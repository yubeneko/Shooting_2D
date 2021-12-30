#pragma once

#include <unordered_map>
#include <string>
#include <fmod_studio.hpp>

class AudioSystem
{
public:
	AudioSystem(class Game* game);
	~AudioSystem();

	bool Initialize();
	void Shutdown();
	void Update(float deltaTime);

private:
	class Game* mGame;
	FMOD::Studio::System* mSystem;
	FMOD::System* mCoreSystem;
};