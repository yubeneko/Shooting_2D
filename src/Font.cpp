#include "Font.h"
#include <vector>
#include "Texture.h"

Font::Font(class Game* game)
  : mGame(game)
{
}

Font::~Font()
{
}

bool Font::Load(const std::string& fileName)
{
	// サポートするフォントサイズ
	// clang-format off
	int fontSizes[] = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};
	// clang-format on

	for (auto fontSize : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), fontSize);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), fontSize);
			return false;
		}
		mFontData.emplace(fontSize, font);
	}

	return true;
}

void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::RenderText(
	const std::string& text,
	const glm::vec3& color /* = Color::White */,
	int pointSize /* = 24 */)
{
	Texture* texture = nullptr;
	SDL_Color sdlColor;
	// カラーを0~1の範囲から0~255に変換する
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;

		// 折り返しを有効にする(200pxを超えたら折り返し)
		SDL_Surface* surf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), sdlColor, 600);
		//SDL_Surface* surf = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
		if (surf != nullptr)
		{
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported.", pointSize);
	}

	return texture;
}