#include "PauseMenu.h"
#include "Game.h"
#include "InputSystem.h"
#include "UIText.h"
#include "UIButton.h"
#include "GameLogic.h"

PauseMenu::PauseMenu(Game* game)
  : UIScreen(game)
{
	mGame->SetState(Game::GameState::EPaused);
	mGame->SetInputMode(Game::InputMode::EUIWindow);
	new UIText("Pause Menu", this, glm::vec2(0.0f, 300.0f));

	// ゲームを続けるボタン
	new UIButton(
		[this]() {
			mGame->SetState(Game::EGamePlay);
			mGame->SetInputMode(Game::InputMode::EGamePlaying);
			Close();
		},
		this, glm::vec2(0.0f, 200.0f));
	new UIText("Resume", this, glm::vec2(0.0f, 200.0f));

	// タイトルシーンに戻るボタン
	new UIButton(
		[this]() {
			Close();
			GameLogic::LoadTitleScene(mGame);
		},
		this, glm::vec2(0.0f, 140.0f));
	new UIText("Back to Title", this, glm::vec2(0.0f, 140.0f));
}