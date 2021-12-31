#pragma once

#include <string>

class SoundEvent
{
public:
	SoundEvent();
	// 対応する FMOD イベントインスタンスが存在するかどうか
	bool IsValid();
	// event のリスタート
	void Restart();
	// ストップ
	void Stop(bool allowFadeOut = true);

	// セッター
	void SetPaused(bool paused);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);

	// ゲッター
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name) const;

protected:
	friend class AudioSystem;
	// AudioSystem クラスはフレンドクラスなので、AudioSystemクラスは
	// この protected なコンストラクタを呼び出すことが可能
	SoundEvent(class AudioSystem* system, unsigned int id);

private:
	class AudioSystem* mSystem;
	unsigned int mID;
};