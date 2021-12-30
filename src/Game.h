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

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadData();
	void UnloadData();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class InputSystem* mInputSystem;
	class PhysWorld* mPhysWorld;
	class AudioSystem* mAudioSystem;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;
};