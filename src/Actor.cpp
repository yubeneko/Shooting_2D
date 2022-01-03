#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include "InputSystem.h"

Actor::Actor(Game* game, const glm::vec2& position)
  : mState(EActive),
	mPosition(position),
	mScale(1.0f),
	mRotation(0.0f),
	mRecomputeWorldTransform(true),
	mName("Default"),
	mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// このようにしているのはComponent のデストラクタでオーナーの Actor の
	// RemoveComponent() を呼び出すため
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		if (comp->GetEnabled())
		{
			comp->Update(deltaTime);
		}
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const struct InputState& keyState)
{
	if (mState == EActive)
	{
		for (auto comp : mComponents)
		{
			if (comp->GetEnabled())
			{
				comp->ProcessInput(keyState);
			}
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const struct InputState& keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(mPosition, 0.0f));
		glm::mat4 rotation = glm::rotate(translate, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
		mWorldTransform = glm::scale(rotation, glm::vec3(mScale, mScale, 1.0f));

		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	int order = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (order < (*iter)->GetUpdateOrder()) { break; }
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

template <typename T>
T* Actor::GetComponent()
{
	for (auto c : mComponents)
	{
		if (typeid(*c) == typeid(T))
		{
			return dynamic_cast<T*>(c);
		}
	}

	return nullptr;
}