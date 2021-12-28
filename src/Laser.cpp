#include "Laser.h"
#include "CircleCollider.h"
#include "EnemyShip.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"

Laser::Laser(Game* game)
  : Actor(game),
	mDeathTimer(3.0f),
	mSpeed(300.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(GetGame()->GetRenderer()->GetTexture("Assets/Laser.png"));
	CircleCollider* cc = new CircleCollider(this);
	cc->SetRadius(10.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
		return;
	}

	glm::vec2 pos = GetPosition();
	pos.x += mSpeed * deltaTime;
	SetPosition(pos);
}

void Laser::OnCollision(CircleCollider* collider)
{
	Actor* other = collider->GetOwner();

	// プレイヤーとの衝突は無視
	if (other->GetTag() == "Player") { return; }

	if (other->GetTag() == "Enemy")
	{
		other->SetState(EDead);
		SetState(EDead);
	}
}