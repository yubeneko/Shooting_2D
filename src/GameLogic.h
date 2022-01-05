#pragma once

#include <functional>
#include <vector>
#include <chrono>

class GameLogic
{
public:
	static void LoadTitleScene(class Game* game);
	static void LoadGameScene(class Game* game);
	static void GameOverProcess(class Game* game);

private:
	static std::chrono::system_clock::time_point mGameStartTime;
};