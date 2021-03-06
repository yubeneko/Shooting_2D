#include "CircleCollider.h"
#include <glm/gtx/norm.hpp>
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"

CircleCollider::CircleCollider(Actor* owner)
  : Component(owner),
	mCircle(glm::vec2(
				owner->GetPosition().x,
				owner->GetPosition().y),
			1.0f)
{
	owner->GetGame()->GetPhysWorld()->AddCircle(this);
}

CircleCollider::~CircleCollider()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveCircle(this);
}

void CircleCollider::OnUpdateWorldTransform()
{
	mCircle.mCenter = mOwner->GetPosition();
}