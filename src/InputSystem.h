#pragma once
#include <SDL_scancode.h>
#include <glm/glm.hpp>

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

class MouseState
{
public:
	friend class InputSystem;

	// 座標は画面の中心を原点とする座標
	const glm::vec2 GetPosition() const { return mMousePos; }
	const glm::vec2 GetScrollWheel() const { return mScrollWheel; }

	// マウスのボタンには
	// SDL_BUTTON_LEFT
	// SDL_BUTTON_RIGHT
	// SDL_BUTTON_MIDDLE
	// SDL_BUTTON_X1
	// SDL_BUTTON_X2
	// がある。

	bool GetButtonValue(int button) const;
	bool GetButtonDown(int button) const;
	bool GetButtonUp(int button) const;
	bool GetMouseMode() const { return mIsRelative; }

private:
	glm::vec2 mMousePos;
	glm::vec2 mScrollWheel;

	// マウスの状態はビット列で表される

	Uint32 mCurrButtons;
	Uint32 mPrevButtons;

	// マウスの移動が相対移動かどうか
	bool mIsRelative;
};

struct InputState
{
	KeyboardState keyboard;
	MouseState mouse;
};

class InputSystem
{
public:
	InputSystem(class Game* game);
	bool Initialize();
	void Shutdown();

	// イベントのポーリング前に呼ばれる
	void PrepareForUpdate();
	// イベントのポーリング後に呼ばれる
	void Update();
	const InputState& GetState() const { return mState; }
	void ProcessEvent(union SDL_Event& event);

	void SetRelativeMouseMode(bool value);

private:
	InputState mState;
	class Game* mGame;
};