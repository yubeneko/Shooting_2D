#include "GameLogic.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

#include "PlayerShip.h"
#include "EnemyShipGenerator.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "TitleScreen.h"
#include "ResultScreen.h"
#include "AudioSystem.h"

#include <vector>

std::chrono::system_clock::time_point GameLogic::mGameStartTime;
SoundEvent GameLogic::mBGM;

void GameLogic::LoadTitleScene(Game* game)
{
	// シーンのロード前に前のシーンのアクターを全て破棄する
	game->UnloadAllActors();

	// タイトルUI画面を作る
	new TitleScreen(game);

	Renderer* const renderer = game->GetRenderer();

	// 背景用アクター
	Actor* bgActor = new Actor(game, glm::vec2(0.0f, 0.0f));

	// 背景その1
	BGSpriteComponent* bgsc = new BGSpriteComponent(bgActor);
	bgsc->SetBGTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Farback01.png"),
		renderer->GetTexture("Assets/Farback02.png")});
	bgsc->SetScrollSpeed(-100.0f);

	// 背景その2
	BGSpriteComponent* bgsc2 = new BGSpriteComponent(bgActor, 50);
	bgsc2->SetBGTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Stars.png"),
		renderer->GetTexture("Assets/Stars.png")});
	bgsc2->SetScrollSpeed(-200.0f);

	// ゲームステートをタイトルシーンに変更
	game->SetState(Game::GameState::ETitleScene);

	// 対応するインスタンスがあればストップ
	if (mBGM.IsValid())
	{
		mBGM.Stop();
	}
}

void GameLogic::LoadGameScene(Game* game)
{
	// シーンのロード前に前のシーンのアクターを全て破棄する
	game->UnloadAllActors();

	Renderer* const renderer = game->GetRenderer();

	// プレイヤー操縦機
	Actor* playerShip = new PlayerShip(game, glm::vec2(0.0f, 0.0f));
	playerShip->SetTag("Player");

	// 敵のスポナーを生成
	new EnemyShipGenerator(game);

	// 背景用アクター
	Actor* bgActor = new Actor(game, glm::vec2(0.0f, 0.0f));

	// 背景その1
	BGSpriteComponent* bgsc = new BGSpriteComponent(bgActor);
	bgsc->SetBGTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Farback01.png"),
		renderer->GetTexture("Assets/Farback02.png")});
	bgsc->SetScrollSpeed(-100.0f);

	// 背景その2
	BGSpriteComponent* bgsc2 = new BGSpriteComponent(bgActor, 50);
	bgsc2->SetBGTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Stars.png"),
		renderer->GetTexture("Assets/Stars.png")});
	bgsc2->SetScrollSpeed(-200.0f);

	// ゲームステートをゲームプレイ状態に変更
	game->SetState(Game::GameState::EGamePlay);

	// スタートした時間を記録
	mGameStartTime = std::chrono::system_clock::now();

	// BGM再生

	// まだ対応するインスタンスがなければ新しく生成し、あればリスタートさせる
	if (!mBGM.IsValid())
	{
		mBGM = game->GetAudioSystem()->PlayEvent("event:/BGM");
	}
	else
	{
		mBGM.Restart();
	}
}

void GameLogic::GameOverProcess(Game* game)
{
	game->SetState(Game::GameState::EResultScene);

	// 耐え抜いた時間を計算
	auto finishTime = std::chrono::system_clock::now();
	auto diff = finishTime - mGameStartTime;
	auto time = std::chrono::duration_cast<std::chrono::seconds>(diff).count();

	new ResultScreen(game, time);
}