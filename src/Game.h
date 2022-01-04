#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() const { return mRenderer; }
	class PhysWorld* GetPhysWorld() const { return mPhysWorld; }
	class AudioSystem* GetAudioSystem() const { return mAudioSystem; }

	enum GameState
	{
		EGamePlay,
		EPaused,
		EQuit,
	};

	GameState GetState() const { return mGameState; }
	void SetState(GameState state) { mGameState = state; }

	class Font* GetFont(const std::string& fileName);
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen* screen);

	// アクターを全部破棄する
	void UnloadAllActors();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// ゲームのリソースのアンロードを行う
	// ゲームを終了する前に呼ぶ
	void UnloadData();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class InputSystem* mInputSystem;
	class PhysWorld* mPhysWorld;
	class AudioSystem* mAudioSystem;

	Uint32 mTicksCount;
	GameState mGameState;
	bool mUpdatingActors;

	std::unordered_map<std::string, class Font*> mFonts;
	std::vector<class UIScreen*> mUIStack;

	class UIScreen* mHUD;
};