#pragma once

#include "Component.h"

class StraightEnemyMove : public Component
{
public:
	StraightEnemyMove(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetRightSpeed() const { return mRightSpeed; }
	void SetRightSpeed(float speed) { mRightSpeed = speed; }

private:
	float mRightSpeed;
};