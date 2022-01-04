#include "PhysWorld.h"
#include <algorithm>
#include "Collision.h"
#include "CircleCollider.h"
#include "Actor.h"

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
	// スイープ&プルーンによる衝突テスト

	// まずは円の最小のバウンディングボリュームにおける最小のx座標でソート
	std::sort(mCircleColliders.begin(),
			  mCircleColliders.end(),
			  [](CircleCollider* a, CircleCollider* b) {
				  float aMinX = a->GetCircle().mCenter.x - a->GetCircle().mRadius;
				  float bMinX = b->GetCircle().mCenter.x - b->GetCircle().mRadius;
				  return aMinX < bMinX;
			  });

	for (size_t i = 0; i < mCircleColliders.size(); i++)
	{
		// 現在注目している円
		CircleCollider* a = mCircleColliders[i];

		// 現在注目中のCircleColliderが無効な状態になっているならば
		// そのコライダーは他のコライダーと衝突しない
		if (a->GetEnabled() == false) { break; }

		// バウンディングボリュームにおける最大のx座標を保持
		float max = a->GetCircle().mCenter.x + a->GetCircle().mRadius;

		for (size_t j = i + 1; j < mCircleColliders.size(); j++)
		{
			CircleCollider* b = mCircleColliders[j];

			// 相手のコライダーが無効になっているならばそのコライダーとは衝突しない
			if (b->GetEnabled() == false) { break; }

			// 注目中の円と、それと比較する円の位置関係を調べ、x軸上で重なりがなければ
			// 現在注目している円はそれ以降どんな円とも衝突しない
			if (max < b->GetCircle().mCenter.x - b->GetCircle().mRadius)
			{
				break;
			}
			else if (InterSect(a->GetCircle(), b->GetCircle()))
			{
				// お互いの Actor の OnCollision を呼び出す
				a->GetOwner()->OnCollision(b);
				b->GetOwner()->OnCollision(a);
			}
		}
	}
}