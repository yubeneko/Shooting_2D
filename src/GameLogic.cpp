#include "GameLogic.h"
#include "Game.h"
#include "Ship.h"
#include "PlayerInputMove.h"
#include "BGSpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include <vector>

void GameLogic::LoadData(Game* game)
{
	Actor* ship = new Ship(game);
	PlayerInputMove* pim = new PlayerInputMove(ship);

	Actor* bgActor = new Actor(game);
	BGSpriteComponent* bgsc = new BGSpriteComponent(bgActor);

	bgsc->SetBGTextures(std::vector<Texture*>{
		game->GetRenderer()->GetTexture("Assets/Farback01.png"),
		game->GetRenderer()->GetTexture("Assets/Farback02.png")});
	bgsc->SetScrollSpeed(-100.0f);

	BGSpriteComponent* bgsc2 = new BGSpriteComponent(bgActor, 50);
	bgsc2->SetBGTextures(std::vector<Texture*>{
		game->GetRenderer()->GetTexture("Assets/Stars.png"),
		game->GetRenderer()->GetTexture("Assets/Stars.png")});
	bgsc2->SetScrollSpeed(-200.0f);
}