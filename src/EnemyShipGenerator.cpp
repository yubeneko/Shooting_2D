#include "EnemyShipGenerator.h"
#include "StraightEnemyMove.h"
#include "Game.h"

EnemyShipGenerator::EnemyShipGenerator(Game* game)
  : Actor(game, glm::vec2(0.0f, 0.0f)),
	mGenerateInterbal(2.0f),
	mTimer(0.0f)
{
}

void EnemyShipGenerator::UpdateActor(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer > mGenerateInterbal)
	{
		// タイマーリセット
		mTimer = 0.0f;
		// 敵機
		Actor* enemyShip = new EnemyShip(GetGame(), glm::vec2(300.0f, 0.0f));
		StraightEnemyMove* sem = new StraightEnemyMove(enemyShip);
		sem->SetRightSpeed(-100.0f);
		enemyShip->SetTag("Enemy");
	}
}