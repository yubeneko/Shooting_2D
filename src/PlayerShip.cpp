#include "PlayerShip.h"
#include "CircleCollider.h"
#include "InputSystem.h"
#include "Laser.h"

PlayerShip::PlayerShip(Game* game)
  : Actor(game),
	mLaserCooldownTime(0.5f),
	mLaserCooldownTimer(0.5f)
{
}

void PlayerShip::ActorInput(const struct InputState& keyState)
{
	if (keyState.keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && mLaserCooldownTimer <= 0.0f)
	{
		// タイマーリセット
		mLaserCooldownTimer = mLaserCooldownTime;
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
	}
}

void PlayerShip::UpdateActor(float deltaTime)
{
	mLaserCooldownTimer -= deltaTime;
}

void PlayerShip::OnCollision(CircleCollider* circleCollider)
{
	std::string tag = circleCollider->GetOwner()->GetTag();
}