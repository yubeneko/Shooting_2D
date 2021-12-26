#include "Ship.h"
#include "InputSystem.h"
#include <glm/glm.hpp>
#include "AnimSpriteComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "Texture.h"

Ship::Ship(Game* game)
  : Actor(game)
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