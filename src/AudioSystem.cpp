#include "AudioSystem.h"
#include <SDL.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

unsigned int AudioSystem::sNextID = 0;

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
	// 処理1: ストップした EventInstance を破棄する

	std::vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		FMOD::Studio::EventInstance* e = iter.second;
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			// イベントを開放
			e->release();
			// 終了リストに追加
			done.emplace_back(iter.first);
		}
	}

	// 終了リストに入っている id の EventInstance を連想配列から除去
	for (auto id : done) { mEventInstances.erase(id); }

	// 処理2: FMOD システムの更新
	mSystem->update();
}

void AudioSystem::Shutdown()
{
	UnloadAllBanks();
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

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	unsigned int retID = 0;
	auto iter = mEvents.find(name);

	// 指定されたイベントがあれば再生する
	if (iter != mEvents.end())
	{
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			event->start();
			sNextID++;
			retID = sNextID;
			mEventInstances.emplace(retID, event);
		}
	}
	return SoundEvent(this, retID);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}