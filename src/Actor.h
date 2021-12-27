#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

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
	void ProcessInput(const struct InputState& keyState);
	virtual void ActorInput(const struct InputState& keyState);

	// Componentの追加/削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// Component の取得
	template <typename T>
	T* GetComponent();

	// Getter系
	State GetState() const { return mState; }
	const glm::vec2& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	const glm::mat4& GetWorldTransform() const { return mWorldTransform; }
	class Game* GetGame() const { return mGame; }
	const std::string& GetTag() const { return mTag; }

	// 衝突時に呼ばれる
	virtual void OnCollision(class CircleCollider* circleCollidere) {};

	// 前方ベクトル
	glm::vec2 GetForward() const
	{
		return glm::vec2(glm::cos(mRotation), glm::sin(mRotation));
	}

	// Setter系
	void SetState(State state) { mState = state; }
	void SetTag(const std::string& tag) { mTag = tag; }
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
	std::string mTag;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};