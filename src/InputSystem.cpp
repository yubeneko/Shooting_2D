#include "InputSystem.h"
#include <SDL.h>
#include <cstring>	// memset()
#include "Game.h"
#include "Renderer.h"

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	// 単純に現在指定されたキーが押されているかどうか調べる
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

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & mCurrButtons) != 0;
}

bool MouseState::GetButtonDown(int button) const
{
	// 現在のフレームで押されていて、前のフレームで押されていない場合に true
	int mask = SDL_BUTTON(button);
	return (
		(mask & mPrevButtons) == 0 &&
		(mask & mCurrButtons) != 0);
}

bool MouseState::GetButtonUp(int button) const
{
	// 現在のフレームで離されて、前のフレームで押されていた場合に true
	int mask = SDL_BUTTON(button);
	return (
		(mask & mPrevButtons) != 0 &&
		(mask & mCurrButtons) == 0);
}

InputSystem::InputSystem(Game* game)
  : mGame(game)
{
}

bool InputSystem::Initialize()
{
	// キーボード
	mState.keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// 前フレームの状態格納用の配列の初期化
	memset(mState.keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	// マウス
	// 押下状態を表す変数を初期化しておく
	mState.mouse.mCurrButtons = 0;
	mState.mouse.mPrevButtons = 0;

	return true;
}

void InputSystem::PrepareForUpdate()
{
	// 1フレーム前の入力状態を1フレーム前の入力状態を格納する配列にコピー
	memcpy(mState.keyboard.mPrevState,
		   mState.keyboard.mCurrState,
		   SDL_NUM_SCANCODES);

	// マウス
	// 1フレーム前の入力状態を1フレーム前の入力状態を格納するメンバ変数に代入
	mState.mouse.mPrevButtons = mState.mouse.mCurrButtons;
}

void InputSystem::Update()
{
	// マウス入力処理
	int x = 0;
	int y = 0;
	if (mState.mouse.mIsRelative)
	{
		mState.mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mState.mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
		// 座標の原点を画面の左上から画面の中心に変換
		x = x - mGame->GetRenderer()->GetScreenWidth() / 2;
		y = mGame->GetRenderer()->GetScreenHeight() / 2 - y;
	}

	mState.mouse.mMousePos = glm::vec2(
		static_cast<float>(x),
		static_cast<float>(y));
}

void InputSystem::Shutdown()
{
}

void InputSystem::ProcessEvent(union SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEWHEEL:
			mState.mouse.mScrollWheel = glm::vec2(
				static_cast<float>(event.wheel.x),
				static_cast<float>(event.wheel.y));
			break;
		default:
			break;
	}
}

void InputSystem::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	mState.mouse.mIsRelative = value;
}