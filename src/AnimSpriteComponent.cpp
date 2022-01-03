#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder)
  : SpriteComponent(owner, drawOrder),
	mCurrentFrame(0.0f),
	mAnimFPS(24.0f),
	mIsUsingTextureAtlas(false)	 // テクスチャアトラスを使わない
{
}

AnimSpriteComponent::AnimSpriteComponent(Texture* texture, int row, int col, class Actor* owner, int drawOrder)
  : SpriteComponent(owner, drawOrder),
	mAnimFPS(24.0f),
	mIsUsingTextureAtlas(true)	// テクスチャアトラスを使う
{
	// テクスチャをセット
	SetTexture(texture);
	// 画像領域の幅は テクスチャの幅/列数
	mImageAreaWidth = GetTexWidth() / static_cast<float>(col);
	// 画像領域の高さは テクスチャの高さ/行数
	mImageAreaHeight = GetTexHeight() / static_cast<float>(row);

	mUVWidth = 1.0f / col;
	mUVHeight = 1.0f / row;

	float v = 0.0f;
	for (int i = 0; i < row; i++)
	{
		float u = 0.0f;
		for (int j = 0; j < col; j++)
		{
			mUVs.emplace_back(u, v);
			u += mUVWidth;
		}
		v += mUVHeight;
	}
	mCurrentUV = mUVs[0];
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mIsUsingTextureAtlas)
	{
		if (mUVs.size() > 0)
		{
			mCurrentFrame += mAnimFPS * deltaTime;

			while (mCurrentFrame >= mUVs.size())
			{
				mCurrentFrame -= mUVs.size();
			}

			mCurrentUV = mUVs[static_cast<int>(mCurrentFrame)];
		}
	}
	else
	{
		if (mAnimTextures.size() > 0)
		{
			mCurrentFrame += mAnimFPS * deltaTime;

			while (mCurrentFrame >= mAnimTextures.size())
			{
				mCurrentFrame -= mAnimTextures.size();
			}

			SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
		}
	}
}

void AnimSpriteComponent::Draw(Shader* shader, VertexArray* vao)
{
	if (mIsUsingTextureAtlas)
	{
		if (mTexture)
		{
			// clang-format off
			std::vector<float> vertexCoords =
			{
				-0.5f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
			};
			// clang-format on

			std::vector<float> vertices;

			// 頂点配列を作っていく
			int vcCount = 0;
			// 左上
			for (int i = 0; i < 3; i++) { vertices.push_back(vertexCoords[vcCount++]); }
			vertices.push_back(mCurrentUV.x);
			vertices.push_back(mCurrentUV.y);

			// 右上
			for (int i = 0; i < 3; i++) { vertices.push_back(vertexCoords[vcCount++]); }
			vertices.push_back(mCurrentUV.x + mUVWidth);
			vertices.push_back(mCurrentUV.y);

			// 右下
			for (int i = 0; i < 3; i++) { vertices.push_back(vertexCoords[vcCount++]); }
			vertices.push_back(mCurrentUV.x + mUVWidth);
			vertices.push_back(mCurrentUV.y + mUVHeight);

			// 左下
			for (int i = 0; i < 3; i++) { vertices.push_back(vertexCoords[vcCount++]); }
			vertices.push_back(mCurrentUV.x);
			vertices.push_back(mCurrentUV.y + mUVHeight);

			glBindBuffer(GL_ARRAY_BUFFER, vao->GetVertexBufferID());
			glBufferData(
				GL_ARRAY_BUFFER,
				4 * 5 * sizeof(float),	// 4(頂点数) * 5(1つの頂点に含まれる要素数) * float のサイズ
				vertices.data(),
				GL_STATIC_DRAW);

			// もしかしたらインデックスバッファもここで改めて登録しないとダメかも...

			// サイズを切り出す領域のサイズに拡大する
			glm::mat4 scale = glm::scale(
				glm::mat4(1.0f),
				glm::vec3(
					mImageAreaWidth,
					mImageAreaHeight,
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
	else
	{
		// テクスチャを切り替えてアニメーションを行う場合は基底クラスの Draw を利用する
		SpriteComponent::Draw(shader, vao);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// 現在のフレームをリセットして最初のテクスチャをセット
		mCurrentFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}