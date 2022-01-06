#include "UIText.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include "UIScreen.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

UIText::UIText(
	const std::string& showText,
	UIScreen* owner,
	const glm::vec2& position,
	float scale,
	float rotation,
	const std::string& name)
  : UIComponent(owner, position, scale, rotation, name),
	mText(showText),
	mColor(Color::White),
	mPointSize(40.0f)
{
	mFont = owner->GetGame()->GetFont("Assets/Carlito-Regular.ttf");
	mTextTexture = mFont->RenderText(showText);
}

UIText::~UIText()
{
	if (mTextTexture)
	{
		mTextTexture->Unload();
		delete mTextTexture;
	}
}

void UIText::SetText(
	const std::string& text,
	const glm::vec3& color,
	int pointSize)
{
	if (mTextTexture)
	{
		mTextTexture->Unload();
		delete mTextTexture;
		mTextTexture = nullptr;
	}

	mText = text;
	mColor = color;
	mPointSize = pointSize;
	mTextTexture = mFont->RenderText(mText, color, pointSize);
}

void UIText::SetTextColor(const glm::vec3& color)
{
	mColor = color;
	SetText(mText, color);
}

void UIText::SetPointSize(int pointSize)
{
	mPointSize = pointSize;
	SetText(mText, mColor, pointSize);
}

void UIText::DrawTexture(Shader* shader, VertexArray* vao)
{
	SetDefaultVertexBuffer(vao);

	// 短形をテクスチャの幅と高さで拡大する
	glm::mat4 scale = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(
			static_cast<float>(mTextTexture->GetWidth()),
			static_cast<float>(mTextTexture->GetHeight()),
			1.0f));

	glm::mat4 model = GetModelMat() * scale;
	shader->SetMatrixUniform("uModel", glm::value_ptr(model));
	mTextTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}