#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ActorInput(const struct InputState& keyState) override;

private:
	float mRightSpeed;
	float mUpSpeed;
	glm::vec2 mMaxPos;
	glm::vec2 mMinPos;
};