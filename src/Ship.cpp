#include "Ship.h"
#include "InputSystem.h"
#include <glm/glm.hpp>
#include "AnimSpriteComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "Texture.h"

Ship::Ship(Game* game)
  : Actor(game),
	mRightSpeed(0.0f),
	mUpSpeed(0.0f),
	mMaxPos(glm::vec2(
		game->GetRenderer()->GetScreenWidth() / 2.0f,
		game->GetRenderer()->GetScreenHeight() / 2.0f)),
	mMinPos(-mMaxPos)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	Renderer* renderer = GetGame()->GetRenderer();

	asc->SetAnimTextures(std::vector<Texture*>{
		renderer->GetTexture("Assets/Ship01.png"),
		renderer->GetTexture("Assets/Ship02.png"),
		renderer->GetTexture("Assets/Ship03.png"),
		renderer->GetTexture("Assets/Ship04.png"),
	});
}

void Ship::UpdateActor(float deltaTime)
{
	glm::vec2 pos = GetPosition();
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

	SetPosition(pos);
}

void Ship::ActorInput(const InputState& keyState)
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