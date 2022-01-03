#include "UIComponent.h"
#include "UIScreen.h"
#include "VertexArray.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

UIComponent::UIComponent(
	UIScreen* owner,
	const glm::vec2& position,
	float scale,
	float rotation,
	const std::string& name)
  : mOwnerScreen(owner),
	mPosition(position),
	mScale(scale),
	mRotation(rotation),
	mName(name),
	mShouldRecomputeModelMat(true)
{
	// 自分自身をオーナーのUIコンポーネントとして登録
	owner->AddUIComponent(this);
	ComputeModelMatrix();
}

UIComponent::~UIComponent()
{
	// 自分自身をオーナーのUIコンポーネントの配列から取り除く
	mOwnerScreen->RemoveUIComponent(this);
}

void UIComponent::ProcessInput(const struct InputState& state)
{
}

void UIComponent::Update(float deltaTime)
{
	ComputeModelMatrix();
	UpdateUIComponent(deltaTime);
	ComputeModelMatrix();
}

void UIComponent::UpdateUIComponent(float deltaTime)
{
}

void UIComponent::ComputeModelMatrix()
{
	if (!mShouldRecomputeModelMat) { return; }

	mShouldRecomputeModelMat = false;
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(mPosition, 0.0f));
	glm::mat4 rotation = glm::rotate(translate, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
	mModelMat = glm::scale(rotation, glm::vec3(mScale, mScale, 1.0f));
}

void UIComponent::SetDefaultVertexBuffer(VertexArray* vao)
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