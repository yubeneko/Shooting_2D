#include "Renderer.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>  // glm::ortho
#include <glm/ext/matrix_transform.hpp>	  // glm::lookAt
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

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
	// テクスチャの削除
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();
}

void Renderer::Draw()
{
	glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// アルファブレンディングを有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->SetActive();
	mSpriteVAO->SetActive();

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	// フロントバッファとバックバッファの入れ替え
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	int order = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (order < (*iter)->GetDrawOrder()) { break; }
	}
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);

	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}

	return tex;
}

bool Renderer::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	mSpriteShader->SetActive();

	glm::mat4 proj = glm::ortho(-mScreenWidth / 2.0f,
								mScreenWidth / 2.0f,
								-mScreenHeight / 2.0f,
								mScreenHeight / 2.0f,
								0.0f, 10.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 3),	 // カメラのワールド座標系における座標
		glm::vec3(0, 0, 0),	 // 注視する座標
		glm::vec3(0, 1, 0)	 // カメラの上方向
	);

	// ビュー射影行列を作ってシェーダーに渡す
	glm::mat4 viewProj = proj * view;
	mSpriteShader->SetMatrixUniform("uViewProj", glm::value_ptr(viewProj));

	return true;
}

void Renderer::CreateSpriteVerts()
{
	// clang-format off
	// 先頭3つは3次元頂点座標、後の2つはUV座標
	const float vertices[] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	};

	const unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};
	// clang-format on
	mSpriteVAO = new VertexArray(vertices, 4, 5, indices, 6);
}