#include "Laser.h"
#include "CircleCollider.h"
#include "EnemyShip.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include <sstream>

int Laser::mId = 0;

Laser::Laser(Game* game, const glm::vec2& position)
  : Actor(game, position),
	mDeathTimer(3.0f),
	mSpeed(350.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Laser.png"));

	CircleCollider* cc = new CircleCollider(this);
	cc->SetRadius(10.0f);

	std::ostringstream oss;
	oss << "Laser (" << mId << ")";
	SetName(oss.str());
	mId += 1;
	SetTag("Laser");
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		Destroy();
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
		Destroy();
		other->Destroy();
	}
}