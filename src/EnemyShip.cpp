#include "EnemyShip.h"
#include "CircleCollider.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Renderer.h"

EnemyShip::EnemyShip(Game* game, const glm::vec2& position)
  : Actor(game, position),
	mAnimSprite(nullptr),
	mCircleCollider(nullptr),
	mIsDying(false)
{
	SetName("Enemy Ship");
	mAnimSprite = new AnimSpriteComponent(
		GetGame()->GetRenderer()->GetTexture("Assets/Enemy01.png"), 6, 1, this, 50);

	mCircleCollider = new CircleCollider(this);
	mCircleCollider->SetRadius(20.0f);
}

void EnemyShip::UpdateActor(float deltaTime)
{
	// 死にかけフラグが立っていて、爆発アニメーションが終了していたらアクターを死亡状態にする
	if (mIsDying && mAnimSprite->GetIsPlaying() == false)
	{
		SetState(EDead);
	}

	// スクリーンの左端 + ちょっと出たあたりに移動したら破棄する
	if (GetPosition().x < -1.0f * GetGame()->GetRenderer()->GetScreenWidth() / 2.0f - 100.0f)
	{
		SetState(EDead);
	}
}

void EnemyShip::OnCollision(CircleCollider* circleCollider)
{
	Actor* other = circleCollider->GetOwner();

	if (other->GetTag() == "Player")
	{
		other->Destroy();
	}
}

void EnemyShip::Destroy()
{
	if (mIsDying) { return; }

	// 爆発アニメーションに切り替える
	mAnimSprite->SetTextureAtlas(GetGame()->GetRenderer()->GetTexture("Assets/Explosion.png"), 3, 3);
	mAnimSprite->SetIsLooping(false);
	// 死にかけフラグを立てる
	mIsDying = true;
	// 衝突判定を無効化する
	mCircleCollider->SetEnabled(false);
}