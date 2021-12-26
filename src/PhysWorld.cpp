#include "PhysWorld.h"
#include <algorithm>
#include "Collision.h"
#include "CircleCollider.h"
#include <SDL.h>

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

void PhysWorld::TestPairwise()
{
	for (size_t i = 0; i < mCircleColliders.size(); i++)
	{
		for(size_t j = i + 1; j < mCircleColliders.size(); j++)
		{
			CircleCollider* a = mCircleColliders[i];
			CircleCollider* b = mCircleColliders[j];

			if (InterSect(a->GetCircle(), b->GetCircle()))
			{
				SDL_Log("衝突!");
			}
		}
	}
}