#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void OnCollision (class CircleCollider* circleCollider) override;
};