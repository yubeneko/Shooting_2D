#include "Collision.h"
#include <glm/gtx/norm.hpp>

Circle::Circle(const glm::vec2& center, float radius)
  : mCenter(center),
	mRadius(radius)
{
}

bool InterSect(const Circle& a, const Circle& b)
{
	float dsq = glm::length2(a.mCenter - b.mCenter);
	return dsq <= glm::pow(a.mRadius + b.mRadius, 2);
}