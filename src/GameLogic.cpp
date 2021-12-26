#include "GameLogic.h"
#include "Game.h"
#include "Ship.h"
#include "PlayerInputMove.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include <vector>

void GameLogic::LoadData(Game* game)
{
	Renderer* const renderer = game->GetRenderer();

	// プレイヤー操縦機
	Actor* playerShip = new Ship(game);
	AnimSpriteComponent* asc = new AnimSpriteComponent(playerShip);
	asc->SetAnimTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Ship01.png"),
		renderer->GetTexture("Assets/Ship02.png"),
		renderer->GetTexture("Assets/Ship03.png"),
		renderer->GetTexture("Assets/Ship04.png"),
	});
	new PlayerInputMove(playerShip);

	// 敵機
	Actor* enemyShip = new Ship(game);
	AnimSpriteComponent* enemyAsc = new AnimSpriteComponent(enemyShip);
	enemyAsc->SetAnimTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Enemy01.png"),
		renderer->GetTexture("Assets/Enemy02.png"),
		renderer->GetTexture("Assets/Enemy03.png"),
		renderer->GetTexture("Assets/Enemy04.png"),
		renderer->GetTexture("Assets/Enemy05.png"),
		renderer->GetTexture("Assets/Enemy06.png"),
	});
	enemyShip->SetPosition(glm::vec2(300.0f, 0.0f));

	// 背景用アクター
	Actor* bgActor = new Actor(game);

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