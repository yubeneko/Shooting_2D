#include "UIComponent.h"
#include "UIScreen.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

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