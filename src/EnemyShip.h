#pragma once

#include "Actor.h"

class EnemyShip : public Actor
{
public:
	EnemyShip(class Game* game, const glm::vec2& position);

	void OnCollision (class CircleCollider* circleCollider) override;
};