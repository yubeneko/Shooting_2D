#pragma once

#include "Actor.h"

class PlayerShip : public Actor
{
public:
	PlayerShip(class Game* game);

	void OnCollision(class CircleCollider* circleCollider) override;
};