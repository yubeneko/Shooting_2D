#pragma once

#include "UIComponent.h"

// class UIButton : public UIComponent
// {
// public:
// 	// Getter/Setter
// 	void SetHighlighted(bool set) { mHighlighted = set; }
// 	bool GetHighlighted() const { return mHighlighted; }

// 座標がボタンの範囲内に含まれるかどうか
// bool ContainsPoint(const glm::vec2& pt) const;
// void OnClick();

// private:
// 	// ボタンが押された時のイベントハンドラ格納用
// 	std::function<void()> mOnClick;
// 	// ボタンのサイズ(x:幅, y:高さ)
// 	glm::vec2 mDimensions;
// 	bool mHighlighted;
// 	class Texture* mButtonOn;
//  class Texture* mButtonOff;
// };

// ハイライト用ボタンとしないボタンのテクスチャを用意する
// mButtonOn = mGame->GetRenderer()->GetTexture("Assets/ButtonYellow.png");
// mButtonOff = mGame->GetRenderer()->GetTexture("Assets/ButtonBlue.png");