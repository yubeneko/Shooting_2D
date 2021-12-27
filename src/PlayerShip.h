#pragma once

#include "Actor.h"

class PlayerShip : public Actor
{
public:
	PlayerShip(class Game* game);
	void ActorInput(const struct InputState& keyState) override;
	void UpdateActor(float deltaTime) override;

	void OnCollision(class CircleCollider* circleCollider) override;

private:
	float mLaserCooldownTime;
	float mLaserCooldownTimer;
};