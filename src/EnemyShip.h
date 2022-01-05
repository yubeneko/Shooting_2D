#pragma once

#include "Actor.h"

class EnemyShip : public Actor
{
public:
	EnemyShip(class Game* game, const glm::vec2& position, float randomNumber);

	void UpdateActor(float deltaTime) override;
	void OnCollision (class CircleCollider* circleCollider) override;
	void Destroy() override;

private:
	class AnimSpriteComponent* mAnimSprite;
	class CircleCollider* mCircleCollider;
	bool mIsDying;
};