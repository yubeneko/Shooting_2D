#include "AudioSystem.h"
#include <SDL.h>
#include <fmod_errors.h>

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
		FMOD_DEBUG_LEVEL_ERROR, // エラーだけをログに出力
		FMOD_DEBUG_MODE_TTY // 標準出力に出力
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
		512, // 最大同時発音数
		FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL,
		nullptr
	);

	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	mSystem->getCoreSystem(&mCoreSystem);

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