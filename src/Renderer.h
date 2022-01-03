#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	class Texture* GetTexture(const std::string& fileName);
	class VertexArray* GetSpriteVAO() const { return mSpriteVAO; }

private:

	bool LoadShaders();
	void CreateSpriteVerts();

	std::unordered_map<std::string, class Texture*> mTextures;
	std::vector<class SpriteComponent*> mSprites;

	class Game* mGame;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVAO;

	glm::mat4 mView;
	glm::mat4 mProjection;

	float mScreenWidth;
	float mScreenHeight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};