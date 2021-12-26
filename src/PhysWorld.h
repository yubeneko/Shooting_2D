#pragma once

#include <vector>

class PhysWorld
{
public:
	PhysWorld(class Game* game);
	void AddCircle(class CircleCollider* circle);
	void RemoveCircle(class CircleCollider* circle);

	void TestPairwise();

private:
	class Game* mGame;
	std::vector<class CircleCollider*> mCircleColliders;
};