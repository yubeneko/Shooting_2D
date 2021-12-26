#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class PlayerInputMove : public Component
{
public:
	PlayerInputMove(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	void ProcessInput(const struct InputState& keyState) override;

private:
	float mRightSpeed;
	float mUpSpeed;
	glm::vec2 mMaxPos;
	glm::vec2 mMinPos;
};