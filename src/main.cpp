#include <SDL.h>
#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Graphics
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

SDL_Window* g_main_window;
SDL_GLContext g_glContex;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL_Init failed with error: " << SDL_GetError()
				  << std::endl;
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	g_main_window = SDL_CreateWindow(
		"window",
		100,
		100,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (g_main_window == nullptr)
	{
		std::cout << "Unable to crete the main window. Error: " << SDL_GetError()
				  << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	g_glContex = SDL_GL_CreateContext(g_main_window);

	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW");
		return EXIT_FAILURE;
	}

	return true;
}

void Shutdown()
{
	if (g_main_window != nullptr)
	{
		SDL_DestroyWindow(g_main_window);
		g_main_window = nullptr;
	}

	SDL_Quit();
}

int main()
{
	// 初期化
	if (Init() == false)
	{
		Shutdown();
	}

	Shader shader;
	shader.Load("Shaders/Simple.vert", "Shaders/Simple.frag");

	// clang-format off
	const float verts[] =
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
	VertexArray vertexArray(verts, 4, 3, indices, 6);

	glm::mat4 proj = glm::ortho(-512.0f, 512.0f, -384.0f, 384.0f, 0.0f, 10.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 3),	 // カメラのワールド座標系における座標
		glm::vec3(0, 0, 0),	 // 注視する座標
		glm::vec3(0, 1, 0)	 // Head is up (set to 0,-1,0 to look upside-down)
	);

	glm::mat4 viewProj = proj * view;

	glm::mat4 identity = glm::mat4(1.0f);
	// 最初は拡大/縮小行列
	glm::mat4 scaling = glm::scale(identity, glm::vec3(30.0, 30.0, 1.0));
	// 次は回転行列
	glm::mat4 rotation = glm::rotate(
		scaling,
		static_cast<float>(glm::radians(0.0)),
		glm::vec3(0.0, 0.0, 1.0));

	// 最後に平行移動行列をかけて、最終的なモデル行列とする
	glm::mat4 model = glm::translate(rotation, glm::vec3(10.0f, 1.0f, 0.0f));

	// 実行ループ
	SDL_Event event;
	bool running = true;
	while (running)
	{
		// Check and process I/O events
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN: {
					running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE;
					break;
				}
				case SDL_QUIT: {
					running = false;
					break;
				}
				default:
					break;
			}
		}

		// 描画
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		vertexArray.SetActive();
		shader.SetActive();
		shader.SetMatrixUniform("model", glm::value_ptr(model));
		shader.SetMatrixUniform("view_proj", glm::value_ptr(viewProj));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(g_main_window);
	}

	Shutdown();
	return EXIT_SUCCESS;
}
