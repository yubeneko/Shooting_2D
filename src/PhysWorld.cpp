#include "PhysWorld.h"
#include <algorithm>

PhysWorld::PhysWorld(Game* game)
  : mGame(game)
{
}

void PhysWorld::AddCircle(CircleCollider* circle)
{
	mCircleColliders.emplace_back(circle);
}

void PhysWorld::RemoveCircle(CircleCollider* circle)
{
	auto iter = std::find(
		mCircleColliders.begin(),
		mCircleColliders.end(),
		circle);

	if (iter != mCircleColliders.end())
	{
		std::iter_swap(iter, mCircleColliders.end() - 1);
		mCircleColliders.pop_back();
	}
}