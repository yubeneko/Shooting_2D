#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Color.h"
class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	void ProcessInput(const struct InputState& state);
	virtual void UIScreenInput(const struct InputState& state);

	void Update(float deltaTime);
	virtual void UpdateUIScreen(float deltaTime);

	void Draw(class Shader* shader);

	enum UIState
	{
		EActive,
		EClosing,
	};

	void Close();

	UIState GetState() const { return mState; }
	class Game* GetGame() const { return mGame; }

	void AddUIComponent(class UIComponent* uiComp);
	void RemoveUIComponent(class UIComponent* uiComp);

protected:
	class Game* mGame;
	UIState mState;
	std::vector<class UIComponent*> mUIComponents;
};