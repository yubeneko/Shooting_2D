#pragma once

#include "Actor.h"
#include "EnemyShip.h"

class EnemyShipGenerator : public Actor
{
public:
	EnemyShipGenerator(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	float mGenerateInterbal;
	float mTimer;
};