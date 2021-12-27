#include "EnemyShip.h"
#include "CircleCollider.h"
#include <SDL.h>

EnemyShip::EnemyShip(Game* game)
  : Actor(game)
{
}

void EnemyShip::OnCollision(CircleCollider* circleCollider)
{
	std::string tag = circleCollider->GetOwner()->GetTag();

	if (tag == "Player")
	{
		SDL_Log("プレイヤーと衝突!");
	}
}