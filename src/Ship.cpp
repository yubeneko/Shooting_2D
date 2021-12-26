#include "Ship.h"
#include "CircleCollider.h"
#include <SDL.h>

Ship::Ship(Game* game)
  : Actor(game)
{
}

void Ship::OnCollision(CircleCollider* circleCollider)
{
	std::string tag = circleCollider->GetOwner()->GetTag();

	if (tag == "Enemy")
	{
		SDL_Log("敵と衝突!");
	}
	else if (tag == "Player")
	{
		SDL_Log("プレイヤーと衝突!");
	}
}