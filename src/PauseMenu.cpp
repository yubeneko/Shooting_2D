#include "PauseMenu.h"
#include "Game.h"
#include "InputSystem.h"
#include "UIText.h"

PauseMenu::PauseMenu(Game* game)
  : UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	new UIText("Pause Menu", this);
}

PauseMenu::~PauseMenu()
{
	mGame->SetState(Game::EGamePlay);
}

void PauseMenu::UIScreenInput(const struct InputState& keyState)
{
	// テスト用にPキーで閉じるようにしておく
	if (keyState.keyboard.GetKeyDown(SDL_SCANCODE_P))
	{
		Close();
	}
}