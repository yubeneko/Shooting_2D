#include "PlayerShip.h"
#include "CircleCollider.h"
#include <SDL.h>

PlayerShip::PlayerShip(Game* game)
  : Actor(game)
{
}

void PlayerShip::OnCollision(CircleCollider* circleCollider)
{
	std::string tag = circleCollider->GetOwner()->GetTag();
}