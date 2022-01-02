#include "PauseMenu.h"
#include "Game.h"
#include "InputSystem.h"

PauseMenu::PauseMenu(Game* game)
  : UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	SetText("Pause Menu");
	AddButton("Resume", [this]() {
		Close();
	});
	AddButton("Quit", [this]() {
		mGame->SetState(Game::EQuit);
	});
}

PauseMenu::~PauseMenu()
{
	mGame->SetState(Game::EGamePlay);
}

void PauseMenu::ProcessInput(const struct InputState& keyState)
{
	UIScreen::ProcessInput(keyState);

	// テスト用にPキーで閉じるようにしておく
	if (keyState.keyboard.GetKeyDown(SDL_SCANCODE_P))
	{
		Close();
	}
}