#include "Renderer.h"
#include "Game.h"
#include "Shader.h"
#include "VertexArray.h"
#include <glm/ext/matrix_clip_space.hpp> // glm::ortho
#include <glm/ext/matrix_transform.hpp>	 // glm::lookAt
#include <glm/gtc/type_ptr.hpp>

#include<GL/glew.h>

Renderer::Renderer(Game* game)
  : mGame(game),
	mSpriteShader(nullptr),
	mSpriteVAO(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(
		"Shooting 2D",
		100,
		100,
		static_cast<int>(mScreenWidth),
		static_cast<int>(mScreenHeight),
		SDL_WINDOW_OPENGL);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load Shaders.");
		return false;
	}

	CreateSpriteVerts();

	return true;
}

void Renderer::Shutdown()
{
	delete mSpriteVAO;

	mSpriteShader->Unload();
	delete mSpriteShader;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	// ロードしたテクスチャの削除等
}

void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: アルファブレンディングを有効化

	mSpriteShader->SetActive();
	mSpriteVAO->SetActive();

	// TODO: スプライトコンポーネントの Draw を呼び出す

	// フロントバッファとバックバッファの入れ替え
	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Simple.vert", "Shaders/Simple.frag"))
	{
		return false;
	}
	mSpriteShader->SetActive();

	glm::mat4 proj = glm::ortho(-512.0f, 512.0f, -384.0f, 384.0f, 0.0f, 10.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 3),	 // カメラのワールド座標系における座標
		glm::vec3(0, 0, 0),	 // 注視する座標
		glm::vec3(0, 1, 0)	 // カメラの上方向
	);

	glm::mat4 viewProj = proj * view;
	mSpriteShader->SetMatrixUniform("uViewProj", glm::value_ptr(viewProj));

	return true;
}

void Renderer::CreateSpriteVerts()
{
	// clang-format off
	const float vertices[] =
	{
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	const unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};
	// clang-format on
	VertexArray vertexArray(vertices, 4, 3, indices, 6);
}