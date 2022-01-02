#include "UIScreen.h"
#include "Game.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture.h"
#include "Shader.h"
#include "InputSystem.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

UIScreen::UIScreen(Game* game)
  : mGame(game),
	mTextTexture(nullptr),
	mBackground(nullptr),
	mPos(glm::vec2(0.0f, 300.0f)),
	mNextButtonPos(glm::vec2(0.0f, 200.0f)),
	mBGPos(glm::vec2(0.0f, 250.0f)),
	mState(EActive)
{
	game->PushUI(this);
	mFont = mGame->GetFont("Assets/Carlito-Regular.ttf");
	mButtonOn = mGame->GetRenderer()->GetTexture("Assets/ButtonYellow.png");
	mButtonOff = mGame->GetRenderer()->GetTexture("Assets/ButtonBlue.png");
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
	// あれば背景を描画する
	if (mBackground)
	{
		DrawTexture(shader, mBackground, mBGPos);
	}

	// あればテキストを描画する
	if (mTextTexture)
	{
		DrawTexture(shader, mTextTexture, mPos);
	}

	// ボタンの描画
	for (auto b : mButtons)
	{
		// ボタンがハイライトされているかどうかで背景を決める
		Texture* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
		// ボタンの背景を描画する
		DrawTexture(shader, tex, b->GetPosition());
		// ボタンのテキストを描画する
		DrawTexture(shader, b->GetNameTexture(), b->GetPosition());
	}
}

void UIScreen::ProcessInput(const struct InputState& state)
{
	bool isLeftMouseButtonReleased = state.mouse.GetButtonUp(SDL_BUTTON_LEFT);

	// ボタンがマウスカーソルと重なっているかどうかを調べて、
	// ハイライト状態を更新する
	for (auto b : mButtons)
	{
		if (b->ContainsPoint(state.mouse.GetPosition()))
		{
			b->SetHighlighted(true);
		}
		else
		{
			b->SetHighlighted(false);
		}

		if (b->GetHighlighted() && isLeftMouseButtonReleased) { b->OnClick(); }
	}
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
		glm::vec3(offset, 0.0f));

	glm::mat4 model = translateMat * scaleMat;
	shader->SetMatrixUniform("uModel", glm::value_ptr(model));
	texture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	// ボタンの押し範囲はテクスチャのサイズと同等とする
	glm::vec2 dims(
		static_cast<float>(mButtonOn->GetWidth()),
		static_cast<float>(mButtonOn->GetHeight()));

	Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
	mButtons.emplace_back(b);

	// 次のボタンの位置を更新する
	// ボタンとして使うテクスチャ + 余白の分だけ下に下げる
	mNextButtonPos.y -= mButtonOff->GetHeight() + 20.0f;
}

Button::Button(const std::string& name,
			   class Font* font,
			   std::function<void()> onClick,
			   const glm::vec2& pos,
			   const glm::vec2& dims)
  : mOnClick(onClick),
	mNameTex(nullptr),
	mFont(font),
	mPosition(pos),
	mDimensions(dims),
	mHighlighted(false)
{
	SetName(name);
}

Button::~Button()
{
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
	}
}

void Button::SetName(const std::string& name)
{
	mName = name;
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
		mNameTex = nullptr;
	}
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const glm::vec2& pt) const
{
	// 分離軸定理による判定
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
			  pt.x > (mPosition.x + mDimensions.x / 2.0f) ||
			  pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
			  pt.y > (mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	if (mOnClick) { mOnClick(); }
}