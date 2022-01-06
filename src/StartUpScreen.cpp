#include "StartUpScreen.h"
#include "UIImage.h"
#include "Renderer.h"
#include "Game.h"
#include "GameLogic.h"

StartUpScreen::StartUpScreen(Game* game)
  : UIScreen(game),
	mTimer(0.0f)
{
	new UIImage(game->GetRenderer()->GetTexture("Assets/WhiteBack.png"), this);
	UIImage* fmodImage = new UIImage(game->GetRenderer()->GetTexture("Assets/FMOD Logo Black - White Background.png"), this);
	fmodImage->SetScale(0.6f);
}

void StartUpScreen::UpdateUIScreen(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= 4.0f)
	{
		Close();
		GameLogic::LoadTitleScene(mGame);
	}
}