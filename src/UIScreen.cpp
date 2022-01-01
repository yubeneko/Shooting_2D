#include "UIScreen.h"
#include "Game.h"
#include "Font.h"
#include "Texture.h"
#include "Shader.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

UIScreen::UIScreen(Game* game)
  : mGame(game),
	mTextTexture(nullptr),
	mPos(glm::vec2(0.0f, 300.0f)),
	mState(EActive)
{
	game->PushUI(this);
	mFont = mGame->GetFont("Assets/Carlito-Regular.ttf");
}

UIScreen::~UIScreen()
{
	if (mTextTexture)
	{
		mTextTexture->Unload();
		delete mTextTexture;
	}
}

void UIScreen::Update(float deltaTime)
{
}

void UIScreen::Draw(Shader* shader)
{
	if (mTextTexture)
	{
		DrawTexture(shader, mTextTexture, mPos);
	}
}

void UIScreen::ProcessInput(const struct InputState& keyState)
{
}

void UIScreen::HandleKeyPress(int key)
{
}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::SetText(
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

	mTextTexture = mFont->RenderText(text, color, pointSize);
}

void UIScreen::DrawTexture(
	Shader* shader,
	Texture* texture,
	const glm::vec2& offset,
	float scale)
{
	// 短形をテクスチャの幅と高さと、引数で渡されたスケールで拡大
	glm::mat4 scaleMat = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(
			static_cast<float>(texture->GetWidth() * scale),
			static_cast<float>(texture->GetHeight() * scale),
			1.0f));

	// 短形の位置
	glm::mat4 translateMat = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(offset, 0.0f)
	);

	glm::mat4 model = translateMat * scaleMat;
	shader->SetMatrixUniform("uModel", glm::value_ptr(model));
	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}