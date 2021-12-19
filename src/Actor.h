#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead,
	};

	Actor(class Game* game);
	virtual ~Actor();

	// 更新系
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ComputeWorldTransform();

	// 入力系
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	// Componentの追加/削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// Getter系
	State GetState() const { return mState; }
	const glm::vec2& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	class Game* GetGame() const { return mGame; }

	// 前方ベクトル
	glm::vec2 GetForward() const
	{
		return glm::vec2(glm::cos(mRotation), glm::sin(mRotation));
	}

	// Setter系
	void SetState(State state) { mState = state; }
	void SetPosition(const glm::vec2& position)
	{
		mRecomputeWorldTransform = true;
		mPosition = position;
	}
	void SetScale(float scale)
	{
		mRecomputeWorldTransform = true;
		mScale = scale;
	}
	void SetRotation(float rotation)
	{
		mRecomputeWorldTransform = true;
		mRotation = rotation;
	}

private:
	State mState;
	glm::vec2 mPosition;
	float mScale;
	float mRotation; // ラジアン
	glm::mat4 mWorldTransform;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};