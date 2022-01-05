#include "EnemyShip.h"
#include "CircleCollider.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "StraightEnemyMove.h"

EnemyShip::EnemyShip(Game* game, const glm::vec2& position, float randomNumber)
  : Actor(game, position),
	mAnimSprite(nullptr),
	mCircleCollider(nullptr),
	mIsDying(false)
{
	SetName("Enemy Ship");

	mCircleCollider = new CircleCollider(this);
	mCircleCollider->SetRadius(20.0f);

	// x軸スピード
	float speed = -100.0f;

	// 3割の確率でスピードを1.2倍
	// 少し速い機体は色を変える
	if (randomNumber < 0.3f)
	{
		speed *= 1.2f;
		mAnimSprite = new AnimSpriteComponent(
			GetGame()->GetRenderer()->GetTexture("Assets/Enemy02.png"), 6, 1, this, 50);
	}
	else
	{
		mAnimSprite = new AnimSpriteComponent(
			GetGame()->GetRenderer()->GetTexture("Assets/Enemy01.png"), 6, 1, this, 50);
	}

	StraightEnemyMove* sem = new StraightEnemyMove(this);
	sem->SetRightSpeed(speed);
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