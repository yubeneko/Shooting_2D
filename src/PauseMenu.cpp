#include "PauseMenu.h"
#include "Game.h"
#include "InputSystem.h"

PauseMenu::PauseMenu(Game* game)
  : UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	SetText(
		"Pause Menu"
	);
}

PauseMenu::~PauseMenu()
{
	mGame->SetState(Game::EGamePlay);
}

void PauseMenu::ProcessInput(const struct InputState& keyState)
{
	UIScreen::ProcessInput(keyState);

	// Pキーで閉じるようにしておく
	if (keyState.keyboard.GetKeyDown(SDL_SCANCODE_P))
	{
		Close();
	}
}