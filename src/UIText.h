#pragma once

#include "UIComponent.h"
#include "Color.h"

class UIText : public UIComponent
{
public:
	UIText(const std::string& showText,
		   class UIScreen* owner,
		   const glm::vec2& position = glm::vec2(0.0f, 0.0f),
		   float scale = 1.0f,
		   float rotation = 0.0f,
		   const std::string& name = "UIText Component");
	~UIText();

	/**
	 * @brief テキストを新しくセットする
	 *
	 * @param text 表示するテキスト
	 * @param color テキストの色(0~1の範囲で指定)
	 * @param pointSize 表示するサイズ
	 */
	void SetText(
		const std::string& text,
		const glm::vec3& color = Color::White,
		int pointSize = 40);

	void SetTextColor(const glm::vec3& color);
	void SetPointSize(int pointSize);

protected:
	void DrawTexture(class Shader* shader, class VertexArray* vao) override;

private:
	// 描画するテキスト
	std::string mText;
	// テキスト表示用フォント
	class Font* mFont;
	// テキストのテクスチャ
	class Texture* mTextTexture;
	glm::vec3 mColor;
	int mPointSize;
};