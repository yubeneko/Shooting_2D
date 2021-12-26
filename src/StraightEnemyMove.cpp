#include "StraightEnemyMove.h"
#include "Actor.h"

StraightEnemyMove::StraightEnemyMove(Actor* owner, int updateOrder)
  : Component(owner, updateOrder)
{
}

void StraightEnemyMove::Update(float deltaTime)
{
	glm::vec2 pos = mOwner->GetPosition();
	pos.x += mRightSpeed * deltaTime;
	mOwner->SetPosition(pos);
}
