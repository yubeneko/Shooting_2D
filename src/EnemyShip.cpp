#include "EnemyShip.h"
#include "CircleCollider.h"
#include <SDL.h>

EnemyShip::EnemyShip(Game* game, const glm::vec2& position)
  : Actor(game, position)
{
	SetName("Enemy Ship");
}

void EnemyShip::OnCollision(CircleCollider* circleCollider)
{
	Actor* other = circleCollider->GetOwner();

	if (other->GetTag() == "Player")
	{
		other->SetState(Actor::EDead);
	}
}