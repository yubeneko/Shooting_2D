#pragma once

#include "UIScreen.h"

class StartUpScreen : public UIScreen
{
public:
	StartUpScreen(class Game* game);

	void UpdateUIScreen(float deltaTime) override;

private:
	float mTimer;
};