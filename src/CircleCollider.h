#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class CircleCollider : public Component
{
public:
	CircleCollider(class Actor* owner);

	float GetRadius() const { return mRadius; }
	void SetRadius(float radius) { mRadius = radius; }

	glm::vec2 GetCenterPosition() const;

private:
	float mRadius;
};