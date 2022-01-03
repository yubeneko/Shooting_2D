#include "PlayerShip.h"
#include "CircleCollider.h"
#include "InputSystem.h"
#include "Laser.h"
#include "AudioSystem.h"
#include "Game.h"
#include "Renderer.h"
#include "Component.h"
#include "AnimSpriteComponent.h"

PlayerShip::PlayerShip(Game* game, const glm::vec2& position)
  : Actor(game, position),
	mAnimSprite(nullptr),
	mIsDying(false),
	mLaserCooldownTime(0.5f),
	mLaserCooldownTimer(0.5f)
{
	SetName("Player");
	mAnimSprite = new AnimSpriteComponent(GetGame()->GetRenderer()->GetTexture("Assets/Ship.png"), 4, 1, this);
}

void PlayerShip::ActorInput(const struct InputState& keyState)
{
	if (keyState.keyboard.GetKeyValue(SDL_SCANCODE_SPACE) && mLaserCooldownTimer <= 0.0f)
	{
		// タイマーリセット
		mLaserCooldownTimer = mLaserCooldownTime;
		glm::vec2 pos = GetPosition();
		pos.x += 40.0f;
		new Laser(GetGame(), pos);
		// SE再生
		GetGame()->GetAudioSystem()->PlayEvent("event:/PlayerShoot");
	}
}

void PlayerShip::UpdateActor(float deltaTime)
{
	mLaserCooldownTimer -= deltaTime;

	// 死にかけフラグが立っていて、爆発アニメーションが終了していたらアクターを死亡状態にする
	if (mIsDying && mAnimSprite->GetIsPlaying() == false)
	{
		SetState(EDead);
	}
}

void PlayerShip::Destroy()
{
	if (mIsDying) { return; }

	// 爆発アニメーションに切り替える
	mAnimSprite->SetTextureAtlas(GetGame()->GetRenderer()->GetTexture("Assets/Explosion.png"), 3, 3);
	mAnimSprite->SetIsLooping(false);
	// 死にかけフラグを立てる
	mIsDying = true;
}

void PlayerShip::OnCollision(CircleCollider* circleCollider)
{
}