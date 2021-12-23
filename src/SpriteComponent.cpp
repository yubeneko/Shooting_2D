#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
  : Component(owner),
	mTexture(nullptr),
	mDrawOrder(drawOrder),
	mTexWidth(0),
	mTexHeight(0)
{
	mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		// サイズをテクスチャのサイズに拡大する
		glm::mat4 scale = glm::scale(
			glm::mat4(1.0f),
			glm::vec3(
				static_cast<float>(mTexWidth),
				static_cast<float>(mTexHeight),
				1.0f));

		// アクターのモデル行列の最初の変換として scale を適用
		// 順番は スケール(画像サイズ分) -> スケール(アクター分) -> 回転 -> 平行移動 となる
		// これにより、アクターの大きさが1の場合にスプライトがオリジナルのテクスチャのサイズで描画されるようになる
		glm::mat4 modelMat = mOwner->GetWorldTransform() * scale;
		shader->SetMatrixUniform("uModel", glm::value_ptr(modelMat));
		mTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}