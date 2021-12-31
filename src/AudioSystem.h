#pragma once

#include <unordered_map>
#include <string>

#include "SoundEvent.h"

// FMOD 関連の前方参照により
// 他のソースファイルに fmod_studio.hpp をインクルードしないようにする
namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};	// namespace Studio
};		// namespace FMOD

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

	class SoundEvent PlayEvent(const std::string& name);

protected:
	friend class SoundEvent;
	// SoundEvent はフレンドクラスなので、このメンバ関数にもアクセスできる
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);

private:
	// イベントインスタンス管理ID
	static unsigned int sNextID;

	class Game* mGame;
	FMOD::Studio::System* mSystem;
	FMOD::System* mCoreSystem;

	// ロードしたバンクの連想配列
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	// イベント名から EventDescription への連想配列
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	// 生成した EventInstance の連想配列
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
};