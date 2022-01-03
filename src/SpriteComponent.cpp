#include "SpriteComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "VertexArray.h"

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

void SpriteComponent::Draw(Shader* shader, VertexArray* vao)
{
	// テクスチャがなければ描画しない
	if (!mTexture) { return; }

	// デフォルトの頂点バッファをGPUにロードする。
	// こうなってしまったのはテクスチャアトラスを利用するコードを書くことになったため。
	// Renderer::Draw にてテクスチャアトラスを使った描画を行う SpriteComponent(主にAnimSpriteComponent) と
	// そうでない SpriteComponent で分岐させて、テクスチャアトラスを使った描画をおこなった後に
	// デフォルトのVAOに戻す処理を入れるようにすると効率がよくなると思われる。
	SetDefaultVertexBuffer(vao);

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

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}

void SpriteComponent::SetDefaultVertexBuffer(VertexArray* vao)
{
	// clang-format off
	// デフォルトの頂点配列
	const float vertices[] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	};

	// スプライト用のVAOはこの関数が呼ばれる前に有効化されているので、
	// 改めて有効化する必要性はない。

	glBindBuffer(GL_ARRAY_BUFFER, vao->GetVertexBufferID());
	glBufferData(
		GL_ARRAY_BUFFER,
		4 * 5 * sizeof(float),	// 4(頂点数) * 5(1つの頂点に含まれる要素数) * float のサイズ
		vertices,
		GL_STATIC_DRAW);
}