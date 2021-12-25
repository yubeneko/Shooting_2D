#pragma once

#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);

	void UpdateActor(float deltaTime) override;
private:
	float mMoveSpeed;
};