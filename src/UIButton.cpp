#include "UIButton.h"
#include "UIScreen.h"
#include "Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "InputSystem.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

UIButton::UIButton(std::function<void()> onClick,
				   UIScreen* owner,
				   const glm::vec2& position,
				   float scale,
				   float rotation,
				   const std::string& name)
  : UIComponent(owner, position, scale, rotation, name),
	mOnClick(onClick),
	mButtonOn(nullptr),
	mButtonOff(nullptr),
	mHighlighted(false)
{
	mButtonOn = owner->GetGame()->GetRenderer()->GetTexture("Assets/ButtonYellow.png");
	mButtonOff = owner->GetGame()->GetRenderer()->GetTexture("Assets/ButtonBlue.png");

	// ボタンの押し範囲はテクスチャのサイズと同等とする
	mClickableSize = glm::vec2(
		static_cast<float>(mButtonOn->GetWidth()),
		static_cast<float>(mButtonOn->GetHeight()));
}

void UIButton::ProcessInput(const struct InputState& state)
{
	UIComponent::ProcessInput(state);
	// ボタンがマウスカーソルと重なっているかどうかを調べて、
	// ハイライト状態を更新する
	if (ContainsPoint(state.mouse.GetPosition()))
	{
		mHighlighted = true;
	}
	else
	{
		mHighlighted = false;
	}

	// もし左マウスボタンが押されていれば、OnClickを呼び出す
	if (mHighlighted && state.mouse.GetButtonUp(SDL_BUTTON_LEFT)) { OnClick(); }
}

bool UIButton::ContainsPoint(const glm::vec2& pt) const
{
	// 分離軸定理による判定
	glm::vec2 pos = GetPosition();
	bool no = pt.x < (pos.x - mClickableSize.x / 2.0f) ||
			  pt.x > (pos.x + mClickableSize.x / 2.0f) ||
			  pt.y < (pos.y - mClickableSize.y / 2.0f) ||
			  pt.y > (pos.y + mClickableSize.y / 2.0f);
	return !no;
}

void UIButton::OnClick()
{
	if (mOnClick) { mOnClick(); }
}

void UIButton::DrawTexture(Shader* shader, VertexArray* vao)
{
	SetDefaultVertexBuffer(vao);

	// ハイライトされているかどうかで利用するテクスチャを使い分ける
	Texture* texture = mHighlighted ? mButtonOn : mButtonOff;

	// 短形をテクスチャの幅と高さで拡大する
	glm::mat4 scale = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(
			static_cast<float>(texture->GetWidth()),
			static_cast<float>(texture->GetHeight()),
			1.0f));
	glm::mat4 model = GetModelMat() * scale;
	shader->SetMatrixUniform("uModel", glm::value_ptr(model));
	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}