#pragma once

#include "UIComponent.h"
#include <functional>

class UIButton : public UIComponent
{
public:
	UIButton(std::function<void()> onClick,
			 class UIScreen* owner,
			 const glm::vec2& position = glm::vec2(0.0f, 0.0f),
			 float scale = 1.0f,
			 float rotation = 0.0f,
			 const std::string& name = "UIButton Component");

	// UIText と違って、破棄するべきリソースは存在しないのでデストラクタは不要。

	void ProcessInput(const struct InputState& state) override;
	// Getter/Setter
	void SetHighlighted(bool set) { mHighlighted = set; }
	bool GetHighlighted() const { return mHighlighted; }

	// 座標がボタンの範囲内に含まれるかどうか
	bool ContainsPoint(const glm::vec2& pt) const;
	// イベントハンドラを呼び出す
	void OnClick();

protected:
	void DrawTexture(class Shader* shader, class VertexArray* vao) override;

private:
	// ボタンが押された時のイベントハンドラ格納メンバ変数
	std::function<void()> mOnClick;
	// ハイライトされた時のボタンのテクスチャ
	class Texture* mButtonOn;
	// ハイライトされていない時のボタンのテクスチャ
	class Texture* mButtonOff;
	// ボタンのサイズ(x:幅, y:高さ)
	glm::vec2 mClickableSize;
	// ハイライトされているか
	bool mHighlighted;
};
