#pragma once

#include "UIScreen.h"

class PauseMenu : public UIScreen
{
public:
	PauseMenu(class Game* game);
	~PauseMenu();

	void UIScreenInput(const struct InputState& keyState) override;
};