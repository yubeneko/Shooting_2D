#include "PlayerInputMove.h"
#include "Actor.h"
#include "InputSystem.h"
#include "Game.h"
#include "Renderer.h"

PlayerInputMove::PlayerInputMove(Actor* owner, int updateOrder)
  : Component(owner, updateOrder),
	mRightSpeed(0.0f),
	mUpSpeed(0.0f),
	mMaxPos(glm::vec2(
		owner->GetGame()->GetRenderer()->GetScreenWidth() / 2.0f,
		owner->GetGame()->GetRenderer()->GetScreenHeight() / 2.0f)),
	mMinPos(-mMaxPos)
{
}

void PlayerInputMove::Update(float deltaTime)
{
	glm::vec2 pos = mOwner->GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mUpSpeed * deltaTime;

	if (pos.x > mMaxPos.x)
	{
		pos.x = mMaxPos.x;
	}

	if (pos.x < mMinPos.x)
	{
		pos.x = mMinPos.x;
	}

	if (pos.y > mMaxPos.y)
	{
		pos.y = mMaxPos.y;
	}

	if (pos.y < mMinPos.y)
	{
		pos.y = mMinPos.y;
	}

	mOwner->SetPosition(pos);
}

void PlayerInputMove::ProcessInput(const InputState& keyState)
{
	mRightSpeed = 0.0f;
	mUpSpeed = 0.0f;

	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mRightSpeed += 300.0f;
	}

	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		mRightSpeed -= 300.0f;
	}

	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		mUpSpeed += 300.0f;
	}

	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		mUpSpeed -= 300.0f;
	}
}