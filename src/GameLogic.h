#pragma once

#include <functional>
#include <vector>

class GameLogic
{
public:
	static void LoadTitleScene(class Game* game);
	static void LoadGameScene(class Game* game);
	static void GameOverProcess(class Game* game);
};