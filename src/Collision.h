#pragma once

#include <glm/glm.hpp>

struct Circle
{
	Circle(const glm::vec2& center, float radius);

	glm::vec2 mCenter;
	float mRadius;
};

bool InterSect(const Circle& a, const Circle& b);