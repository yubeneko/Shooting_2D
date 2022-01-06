#include "TitleScreen.h"
#include "UIText.h"
#include "UIButton.h"
#include "Game.h"
#include "GameLogic.h"
#include "CopyrightScreen.h"

TitleScreen::TitleScreen(Game* game)
  : UIScreen(game)
{
	mGame->SetInputMode(Game::InputMode::EUIWindow);

	new UIText("2D Shooting", this, glm::vec2(0.0f, 300.0f));

	// スタートボタン
	new UIButton(
		[this]() {
			Close();
			mGame->SetInputMode(Game::InputMode::EGamePlaying);
			GameLogic::LoadGameScene(mGame);
		},
		this, glm::vec2(0.0f, 200.0f));
	new UIText("Start", this, glm::vec2(0.0f, 200.0f));

	// ゲーム終了ボタン
	new UIButton([this]() { mGame->SetState(Game::EQuit); }, this, glm::vec2(0.0f, 140.0f));
	new UIText("Quit", this, glm::vec2(0.0f, 140.0f));

	// 権利表記画面表示ボタン
	new UIButton(
		[this]() { new CopyrightScreen(mGame); },
		this, glm::vec2(0.0f, -300.0f));
	new UIText("Copyright", this, glm::vec2(0.0f, -300.0f));
}