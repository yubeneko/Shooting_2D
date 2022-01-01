#pragma once

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include "Color.h"

class Font
{
public:
	Font(class Game* game);
	~Font();

	bool Load(const std::string& fileName);
	void Unload();

	/**
	 * @brief text が書かれたテクスチャを生成して返す
	 *
	 * @param text UIに表示する文字列
	 * @param color UIの色
	 * @param pointSize 文字のサイズ
	 * @return Texture*
	 */
	class Texture* RenderText(
		const std::string& text,
		const glm::vec3& color = Color::White,
		int pointSize = 24);

private:
	// ポイントとフォントの連想配列
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};