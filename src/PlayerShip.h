#pragma once

#include "Actor.h"

class PlayerShip : public Actor
{
public:
	PlayerShip(class Game* game, const glm::vec2& position);
	void ActorInput(const struct InputState& keyState) override;
	void UpdateActor(float deltaTime) override;
	void Destroy() override;
	void OnCollision(class CircleCollider* circleCollider) override;

private:
	class AnimSpriteComponent* mAnimSprite;
	bool mIsDying;
	float mLaserCooldownTime;
	float mLaserCooldownTimer;
};