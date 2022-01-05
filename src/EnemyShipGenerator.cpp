#include "EnemyShipGenerator.h"
#include "Game.h"
#include <random>

EnemyShipGenerator::EnemyShipGenerator(Game* game)
  : Actor(game, glm::vec2(0.0f, 0.0f)),
	mGenerateInterbal(2.0f),
	mTimer(0.0f)
{
}

void EnemyShipGenerator::UpdateActor(float deltaTime)
{
	mTimer += deltaTime;

	// 生成インターバルを段々短くしていく
	// 一番短い生成インターバルは 0.8秒
	if (mGenerateInterbal > 0.8f)
	{
		mGenerateInterbal -= deltaTime * 0.01;
	}

	if (mTimer > mGenerateInterbal)
	{
		// タイマーリセット
		mTimer = 0.0f;

		// 0~1の範囲の乱数を生成する
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<float> distr(0, 1);
		float randNum = distr(eng);

		// 乱数を使って初期値を決めていく
		// y座標は -200 ~ 200 の範囲に変換する
		float yPos = randNum * 2 - 1;
		yPos *= 200;

		// 敵機生成
		Actor* enemyShip = new EnemyShip(GetGame(), glm::vec2(500.0f, yPos), randNum);
		enemyShip->SetTag("Enemy");
	}
}