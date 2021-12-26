#include "CircleCollider.h"
#include <glm/gtx/norm.hpp>
#include "Actor.h"

CircleCollider::CircleCollider(Actor* owner)
  : Component(owner),
	mRadius(10.0f)
{
}

glm::vec2 CircleCollider::GetCenterPosition() const
{
	return mOwner->GetPosition();
}

bool InterSect(const CircleCollider& a, const CircleCollider& b)
{
	float dsq = glm::length2((a.GetCenterPosition() - b.GetCenterPosition()));
	return dsq <= glm::pow(a.GetRadius() + b.GetRadius(), 2);
}