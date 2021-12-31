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

	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	void PlayEvent(const std::string& name);

private:
	class Game* mGame;
	FMOD::Studio::System* mSystem;
	FMOD::System* mCoreSystem;

	// ロードしたバンクの連想配列
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	// イベント名から EventDescription への連想配列
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
};