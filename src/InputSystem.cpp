#include "InputSystem.h"
#include <SDL.h>
#include <cstring>	// memset()

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return mCurrState[keyCode] == 1;
}

bool KeyboardState::GetKeyDown(SDL_Scancode keyCode) const
{
	// 現在のフレームで押されていて、前のフレームで押されていない場合に true
	return mCurrState[keyCode] == 1 && mPrevState[keyCode] == 0;
}

bool KeyboardState::GetKeyUp(SDL_Scancode keyCode) const
{
	// 現在のフレームで離されて、前のフレームで押されていた場合に true
	return mCurrState[keyCode] == 0 && mPrevState[keyCode] == 1;
}

bool InputSystem::Initialize()
{
	// キーボード
	mState.keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// 前フレームの状態格納用の配列の初期化
	memset(mState.keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::PrepareForUpdate()
{
	// 1フレーム前の入力状態を1フレーム前の入力状態を格納する配列にコピー
	memcpy(mState.keyboard.mPrevState,
		   mState.keyboard.mCurrState,
		   SDL_NUM_SCANCODES);
}

void InputSystem::Update()
{
}

void InputSystem::Shutdown()
{
}