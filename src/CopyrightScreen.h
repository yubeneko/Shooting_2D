#pragma once

#include "UIScreen.h"

class CopyrightScreen : public UIScreen
{
public:
	CopyrightScreen(class Game* game);

	void UIScreenInput(const struct InputState& state) override;
	void UpdateUIScreen(float deltaTime) override;

private:
	std::string GetLicenseString();

private:
	class UIText* mUIText;
	class UIImage* mUIImage;
	float mPrevMouseScrollAmountY;
	float mScrollSpeedY;
};