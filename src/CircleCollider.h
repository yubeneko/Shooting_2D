#pragma once

#include "Component.h"
#include "Collision.h"

class CircleCollider : public Component
{
public:
	CircleCollider(class Actor* owner);
	~CircleCollider();

	const Circle& GetCircle() const { return mCircle; }
	void SetRadius(float radius) { mCircle.mRadius = radius; }

	void OnUpdateWorldTransform() override;

private:
	Circle mCircle;
};