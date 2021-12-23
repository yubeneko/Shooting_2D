#include "BGSpriteComponent.h"
#include "Texture.h"
#include "Actor.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
  : SpriteComponent(owner, drawOrder),
	mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& bg : mBGTextures)
	{
		bg.mOffset.x += mScrollSpeed * deltaTime;
		if (bg.mOffset.x < -1.0f * bg.mTexture->GetWidth())
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * bg.mTexture->GetWidth() - 1;
		}
	}
}

void BGSpriteComponent::Draw(Shader* shader)
{
	for (auto& bg : mBGTextures)
	{
		// サイズをテクスチャのサイズに拡大する
		glm::mat4 scale = glm::scale(
			glm::mat4(1.0f),
			glm::vec3(
				static_cast<float>(bg.mTexture->GetWidth()),
				static_cast<float>(bg.mTexture->GetHeight()),
				1.0f));

		// オフセット分の平行移動
		glm::mat4 translate = glm::translate(
			glm::mat4(1.0f),
			glm::vec3(
				static_cast<float>(bg.mOffset.x),
				static_cast<float>(bg.mOffset.y),
				0.0f));

		// 画像サイズ分のスケーリング -> アクターのモデル行列 -> 背景オフセット分の平行移動の順になる変換行列を作る
		glm::mat4 modelMat = translate * mOwner->GetWorldTransform() * scale;
		shader->SetMatrixUniform("uModel", glm::value_ptr(modelMat));
		SetTexture(bg.mTexture);
		mTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
	int count = 0;
	for (auto texture : textures)
	{
		BGTexture bgt;
		bgt.mTexture = texture;
		// xについてはテクスチャの幅ずつオフセットしていく
		bgt.mOffset.x = texture->GetWidth() * count;
		bgt.mOffset.y = 0.0f;
		mBGTextures.emplace_back(bgt);
		count += 1;
	}
}