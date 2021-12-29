#pragma once

#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(Game* game, const glm::vec2& position);

	void UpdateActor(float deltaTime) override;
	void OnCollision(class CircleCollider* circleCollider) override;

private:
	float mDeathTimer;
	float mSpeed;
	static int mId;
};