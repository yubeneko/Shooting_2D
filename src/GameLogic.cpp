#include "GameLogic.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

#include "PlayerShip.h"
#include "EnemyShip.h"
#include "PlayerInputMove.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "StraightEnemyMove.h"
#include "CircleCollider.h"
#include <vector>

void GameLogic::LoadData(Game* game)
{
	Renderer* const renderer = game->GetRenderer();

	// プレイヤー操縦機
	Actor* playerShip = new PlayerShip(game, glm::vec2(0.0f, 0.0f));
	playerShip->SetTag("Player");

	// 敵機
	Actor* enemyShip = new EnemyShip(game, glm::vec2(300.0f, 0.0f));
	StraightEnemyMove* sem = new StraightEnemyMove(enemyShip);
	sem->SetRightSpeed(-100.0f);
	enemyShip->SetTag("Enemy");

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
}