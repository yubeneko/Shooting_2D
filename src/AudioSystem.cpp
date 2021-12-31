#include "AudioSystem.h"
#include <SDL.h>
#include <fmod_errors.h>
#include <vector>

AudioSystem::AudioSystem(Game* game)
  : mGame(game),
	mSystem(nullptr),
	mCoreSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
	// デバッグログの設定
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR,	 // エラーだけをログに出力
		FMOD_DEBUG_MODE_TTY		 // 標準出力に出力
	);

	FMOD_RESULT result;
	// FMOD studio system のオブジェクトを生成
	result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	// FMOD studio system オブジェクトの初期化
	result = mSystem->initialize(
		512,  // 最大同時発音数
		FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL,
		nullptr);

	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	mSystem->getCoreSystem(&mCoreSystem);

	// マスターバンクをロードする
	// 本プロジェクトではバンクはこの2つだけ
	// Master Bank.strings.bank が先にロードされなければならない
	LoadBank("Assets/Master.strings.bank");
	LoadBank("Assets/Master.bank");

	return true;
}

void AudioSystem::Update(float deltaTime)
{
	mSystem->update();
}

void AudioSystem::Shutdown()
{
	if (mSystem)
	{
		mSystem->release();
	}
}

void AudioSystem::LoadBank(const std::string& name)
{
	// 多重読み込み防止
	if (mBanks.find(name) != mBanks.end()) { return; }

	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		name.c_str(),
		FMOD_STUDIO_LOAD_BANK_NORMAL,
		&bank);

	if (result != FMOD_OK)
	{
		SDL_Log("Failed to load Bank file : %s", name.c_str());
		return;
	}

	// バンクを連想配列に追加する
	mBanks.emplace(name, bank);
	// ストリーミング以外のサンプルデータを全てロードする
	bank->loadSampleData();

	// バンク内にあるイベント数を調べる
	int numEvents = 0;
	bank->getEventCount(&numEvents);

	// イベントが存在する場合、イベント記述子のリストを取得し、
	// 連想配列に追加する
	if (numEvents > 0)
	{
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);

		const int maxPathLength = 512;

		char eventName[maxPathLength];
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = events[i];
			// イベントのパス名(例:"event:/PlayerShoot")
			e->getPath(eventName, maxPathLength, nullptr);
			SDL_Log("%s", eventName);
			mEvents.emplace(eventName, e);
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto iter = mBanks.find(name);
	// ロードされていないバンクをアンロードしようとした場合は何もせず return
	if (iter == mBanks.end()) { return; }

	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);

	// バンク内にイベントが含まれていた場合はそのイベントも
	// mEvents から取り除く
	if (numEvents > 0)
	{
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);

		const int maxPathLength = 512;

		char eventName[maxPathLength];
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = events[i];
			e->getPath(eventName, maxPathLength, nullptr);

			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}

	bank->unloadSampleData();
	bank->unload();
	mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : mBanks)
	{
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	mBanks.clear();
	mEvents.clear();
}

void AudioSystem::PlayEvent(const std::string& name)
{
	auto iter = mEvents.find(name);

	// 指定されたイベントがあれば再生する
	if (iter != mEvents.end())
	{
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			event->start();
			event->release();
		}
	}
}