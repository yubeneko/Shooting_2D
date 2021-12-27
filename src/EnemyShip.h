#pragma once

#include "Actor.h"

class EnemyShip : public Actor
{
public:
	EnemyShip(class Game* game);

	void OnCollision (class CircleCollider* circleCollider) override;
};