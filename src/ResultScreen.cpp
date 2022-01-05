#include "ResultScreen.h"
#include "Game.h"
#include "UIText.h"
#include "UIButton.h"
#include "GameLogic.h"
#include <sstream>

ResultScreen::ResultScreen(Game* game, uint64_t time)
  : UIScreen(game)
{
	mGame->SetInputMode(Game::InputMode::EUIWindow);
	new UIText("Game Over", this, glm::vec2(0.0f, 300.0f));

	std::ostringstream oss;
	oss << "Time : " << time << " seconds";

	new UIText(oss.str(), this, glm::vec2(0.0f, 200.0f));

	// リトライボタン
	new UIButton(
		[this]() {
			Close();
			mGame->SetInputMode(Game::InputMode::EGamePlaying);
			GameLogic::LoadGameScene(mGame);
		},
		this, glm::vec2(0.0f, 140.0f));
	new UIText("Retry", this, glm::vec2(0.0f, 140.0f));

	// タイトルに戻るボタン
	new UIButton(
		[this]() {
			Close();
			GameLogic::LoadTitleScene(mGame);
		},
		this, glm::vec2(0.0f, 80.0f));
	new UIText("Back to Title", this, glm::vec2(0.0f, 80.0f));
}
