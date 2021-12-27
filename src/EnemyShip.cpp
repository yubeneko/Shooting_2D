#include "EnemyShip.h"
#include "CircleCollider.h"
#include <SDL.h>

EnemyShip::EnemyShip(Game* game)
  : Actor(game)
{
}

void EnemyShip::OnCollision(CircleCollider* circleCollider)
{
	Actor* other = circleCollider->GetOwner();

	if (other->GetTag() == "Player")
	{
		other->SetState(EDead);
	}
}