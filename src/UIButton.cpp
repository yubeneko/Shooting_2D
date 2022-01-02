#include "UIButton.h"

// Button::Button(const std::string& name,
// 			   class Font* font,
// 			   std::function<void()> onClick,
// 			   const glm::vec2& pos,
// 			   const glm::vec2& dims)
//   : mOnClick(onClick),
// 	mNameTex(nullptr),
// 	mFont(font),
// 	mPosition(pos),
// 	mDimensions(dims),
// 	mHighlighted(false)
// {
// 	SetName(name);
// }

// Button::~Button()
// {
// 	if (mNameTex)
// 	{
// 		mNameTex->Unload();
// 		delete mNameTex;
// 	}
// }

// void Button::SetName(const std::string& name)
// {
// 	mName = name;
// 	if (mNameTex)
// 	{
// 		mNameTex->Unload();
// 		delete mNameTex;
// 		mNameTex = nullptr;
// 	}
// 	mNameTex = mFont->RenderText(mName);
// }

// bool Button::ContainsPoint(const glm::vec2& pt) const
// {
// 	// 分離軸定理による判定
// 	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
// 			  pt.x > (mPosition.x + mDimensions.x / 2.0f) ||
// 			  pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
// 			  pt.y > (mPosition.y + mDimensions.y / 2.0f);
// 	return !no;
// }

// void Button::OnClick()
// {
// 	if (mOnClick) { mOnClick(); }
// }



// ボタンの入力処理
// bool isLeftMouseButtonReleased = state.mouse.GetButtonUp(SDL_BUTTON_LEFT);

// // ボタンがマウスカーソルと重なっているかどうかを調べて、
// // ハイライト状態を更新する
// for (auto b : mButtons)
// {
// 	if (b->ContainsPoint(state.mouse.GetPosition()))
// 	{
// 		b->SetHighlighted(true);
// 	}
// 	else
// 	{
// 		b->SetHighlighted(false);
// 	}

// 	if (b->GetHighlighted() && isLeftMouseButtonReleased) { b->OnClick(); }
// }


// UIScreen の AddButton
// void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
// {
// 	// ボタンの押し範囲はテクスチャのサイズと同等とする
// 	glm::vec2 dims(
// 		static_cast<float>(mButtonOn->GetWidth()),
// 		static_cast<float>(mButtonOn->GetHeight()));

// 	Button* b = new Button(name, mFont, onClick, mNextButtonPos, dims);
// 	mButtons.emplace_back(b);

// 	// 次のボタンの位置を更新する
// 	// ボタンとして使うテクスチャ + 余白の分だけ下に下げる
// 	mNextButtonPos.y -= mButtonOff->GetHeight() + 20.0f;
// }