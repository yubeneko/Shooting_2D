#pragma once

#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(Game* game);

	void UpdateActor(float deltaTime) override;
	void OnCollision(class CircleCollider* circleCollider) override;

private:
	float mDeathTimer;
	float mSpeed;
};