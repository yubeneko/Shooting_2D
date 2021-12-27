#include "Laser.h"
#include "CircleCollider.h"

Laser::Laser(Game* game)
  : Actor(game),
	mDeathTimer(3.0f)
{
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
}

void Laser::OnCollision(CircleCollider* collider)
{
	if (collider->GetOwner()->GetTag() == "Enemy")
	{
	}
}