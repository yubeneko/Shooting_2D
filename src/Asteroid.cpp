#include "Asteroid.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"

Asteroid::Asteroid(Game* game)
  : Actor(game),
	mMoveSpeed(-200.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Asteroid.png"));
}

void Asteroid::UpdateActor(float deltaTime)
{
	glm::vec2 pos = GetPosition();
	pos.x += mMoveSpeed * deltaTime;
	SetPosition(pos);
}