#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Color.h"

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	virtual void ProcessInput(const struct InputState& keyState);
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
	glm::vec2 mPos;
	UIState mState;
};