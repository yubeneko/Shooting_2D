#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <functional>
#include "Color.h"

class Button
{
public:
	Button(
		const std::string& name,
		class Font* font,
		std::function<void()> onClick,
		const glm::vec2& pos,
		const glm::vec2& dims);

	~Button();
	void SetName(const std::string& name);

	// Getter/Setter
	class Texture* GetNameTexture() const { return mNameTex; }
	const glm::vec2 GetPosition() const { return mPosition; }
	void SetHighlighted(bool set) { mHighlighted = set; }
	bool GetHighlighted() const { return mHighlighted; }

	// 座標がボタンの範囲内に含まれるかどうか
	bool ContainsPoint(const glm::vec2& pt) const;
	void OnClick();

private:
	// ボタンが押された時のイベントハンドラ格納用
	std::function<void()> mOnClick;
	// ボタンに描画するテキスト
	std::string mName;
	// テキストのテクスチャ
	class Texture* mNameTex;
	// テキストのフォント
	class Font* mFont;
	// ボタンの座標
	glm::vec2 mPosition;
	// ボタンのサイズ(x:幅, y:高さ)
	glm::vec2 mDimensions;
	bool mHighlighted;
};

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	virtual void ProcessInput(const struct InputState& state);
	virtual void HandleKeyPress(int key);

	enum UIState
	{
		EActive,
		EClosing,
	};

	void Close();

	UIState GetState() const { return mState; }
	void SetText(
		const std::string& text,
		const glm::vec3& color = Color::White,
		int pointSize = 40.0f);

	void AddButton(const std::string& name, std::function<void()> onClick);

protected:
	/**
	 * @brief テクスチャを描画する
	 *
	 * @param shader シェーダー
	 * @param texture テクスチャ
	 * @param offset 短形のオフセット
	 * @param scale 短形のスケール
	 */
	void DrawTexture(
		class Shader* shader,
		class Texture* texture,
		const glm::vec2& offset = glm::vec2(0.0f, 0.0f),
		float scale = 1.0f);

	class Game* mGame;
	class Font* mFont;
	class Texture* mTextTexture;
	class Texture* mBackground;
	class Texture* mButtonOn;
	class Texture* mButtonOff;

	glm::vec2 mPos;
	glm::vec2 mNextButtonPos;
	glm::vec2 mBGPos;

	UIState mState;
	std::vector<Button*> mButtons;
};