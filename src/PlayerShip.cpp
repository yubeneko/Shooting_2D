#include "PlayerShip.h"
#include "CircleCollider.h"
#include "InputSystem.h"
#include "Laser.h"

PlayerShip::PlayerShip(Game* game, const glm::vec2& position)
  : Actor(game, position),
	mLaserCooldownTime(0.5f),
	mLaserCooldownTimer(0.5f)
{
	SetName("Player");
}

void PlayerShip::ActorInput(const struct InputState& keyState)
{
	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_SPACE) && mLaserCooldownTimer <= 0.0f)
	{
		// タイマーリセット
 		mLaserCooldownTimer = mLaserCooldownTime;
		glm::vec2 pos = GetPosition();
		pos.x += 40.0f;
		new Laser(GetGame(), pos);

	}
}

void PlayerShip::UpdateActor(float deltaTime)
{
	mLaserCooldownTimer -= deltaTime;
}

void PlayerShip::OnCollision(CircleCollider* circleCollider)
{
}