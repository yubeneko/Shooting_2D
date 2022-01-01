#pragma once

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	// SOIL でテクスチャをロードする
	bool Load(const std::string& fileName);
	// SDL_Surface を通してテクスチャをロードする
	void CreateFromSurface(struct SDL_Surface* surface);
	void Unload();

	void SetActive();

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};