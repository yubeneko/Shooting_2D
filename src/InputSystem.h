#pragma once
#include <SDL_scancode.h>

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld,
};

class KeyboardState
{
public:
	friend class InputSystem;

	bool GetKeyValue(SDL_Scancode keyCode) const;
	bool GetKeyDown(SDL_Scancode keyCode) const;
	bool GetKeyUp(SDL_Scancode keyCode) const;

private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];

};

struct InputState
{
	KeyboardState keyboard;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	// イベントのポーリング前に呼ばれる
	void PrepareForUpdate();
	// イベントのポーリング後に呼ばれる
	void Update();
	const InputState& GetState() const { return mState; }

private:
	InputState mState;
};