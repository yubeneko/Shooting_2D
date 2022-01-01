#pragma once

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include <glm/glm.hpp>

namespace Color
{
	static const glm::vec3 Black(0.0f, 0.0f, 0.0f);
	static const glm::vec3 White(1.0f, 1.0f, 1.0f);
	static const glm::vec3 Red(1.0f, 0.0f, 0.0f);
	static const glm::vec3 Green(0.0f, 1.0f, 0.0f);
	static const glm::vec3 Blue(0.0f, 0.0f, 1.0f);
}  // namespace Color

class Font
{
public:
	Font(class Game* game);
	~Font();

	bool Load(const std::string& fileName);
	void Unload();

	class Texture* RenderText(
		const std::string& text,
		const glm::vec3& color = Color::White,
		int pointSize = 24);

private:
	// ポイントとフォントの連想配列
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};