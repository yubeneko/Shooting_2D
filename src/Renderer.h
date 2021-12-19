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

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

private:

	bool LoadShaders();
	void CreateSpriteVerts();

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