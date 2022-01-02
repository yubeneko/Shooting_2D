#include "PauseMenu.h"
#include "Game.h"
#include "InputSystem.h"
#include "UIText.h"
#include "UIButton.h"

PauseMenu::PauseMenu(Game* game)
  : UIScreen(game)
{
	mGame->SetState(Game::EPaused);
	new UIText("Pause Menu", this, glm::vec2(0.0f, 300.0f));

	new UIButton([this]() { Close(); }, this, glm::vec2(0.0f, 200.0f));
	new UIText("Resume", this, glm::vec2(0.0f, 200.0f));

	new UIButton([this]() { mGame->SetState(Game::EQuit); }, this, glm::vec2(0.0f, 140.0f));
	new UIText("Quit Game", this, glm::vec2(0.0f, 140.0f));
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