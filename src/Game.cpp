#include "Game.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PhysWorld.h"
#include "Actor.h"
#include "GameLogic.h"
#include "AudioSystem.h"
#include "Font.h"
#include "UIScreen.h"
#include "PauseMenu.h"

#include <algorithm>

Game::Game()
  : mRenderer(nullptr),
	mInputSystem(nullptr),
	mPhysWorld(nullptr),
	mAudioSystem(nullptr),
	mGameState(EGamePlay),
	mUpdatingActors(false)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mInputSystem = new InputSystem(this);
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize Input System");
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	mPhysWorld = new PhysWorld(this);

	mAudioSystem = new AudioSystem(this);
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize Audio System");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf.");
		return false;
	}

	GameLogic::LoadTitleScene(this);

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	UnloadData();
	TTF_Quit();

	if (mPhysWorld) { delete mPhysWorld; }

	if (mInputSystem)
	{
		mInputSystem->Shutdown();
		delete mInputSystem;
	}

	if (mRenderer)
	{
		mRenderer->Shutdown();
		delete mRenderer;
	}

	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
		delete mAudioSystem;
	}

	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::PushUI(UIScreen* screen)
{
	mUIStack.emplace_back(screen);
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mGameState = EQuit;
				break;
			case SDL_MOUSEWHEEL:
				mInputSystem->ProcessEvent(event);
				break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();

	// インプットモードに応じて入力をシーン上のアクターかUIウィンドウのどちらかに流す。
	// ゲームプレイ中にインタラクトできるUIパーツが存在しないため、この仕様でも問題ない。
	if (mInputMode == InputMode::EGamePlaying)
	{
		// イテレーション中にアクターが追加されるとまずいので、
		// イテレーションに入る前に存在していたアクターだけで入力を処理する
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->ProcessInput(state);
		}
		mUpdatingActors = false;
	}
	else if (!mUIStack.empty())
	{
		// UIスタックのトップにあるUIスクリーンに入力データを流す
		mUIStack.back()->ProcessInput(state);
	}

	// mGameState が EGamePlay で、 ESCAPE キーが押されたらポーズメニューを表示する
	// ポーズメニューの表示開始フレームでは入力が処理されなくなるが、問題はないと思われる
	if (mGameState == EGamePlay &&
		state.keyboard.GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		new PauseMenu(this);
	}
}

void Game::UpdateGame()
{
	// 前回のフレームから16ms経過するまで待機
	// つまり、目標のフレームレートは60FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// ゲームがポーズ中でなければシーン中のアクターの更新をする
	if (!(mGameState == EPaused))
	{
		mUpdatingActors = true;
		// 衝突判定
		mPhysWorld->TestPairwise();
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		for (auto pending : mPendingActors)
		{
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	// AudioSystem の更新
	mAudioSystem->Update(deltaTime);

	// UIスクリーンの更新
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}

	// 閉じられたUIの破棄
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			// イテレータが指す要素のオブジェクトを破棄
			delete *iter;
			// erase の戻り値は配列から除去した要素の次の要素を指すイテレータ!
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::UnloadData()
{
	// 全アクターの破棄
	UnloadAllActors();

	// UIScreen はデストラクタで mUIStack から自分自身を取り除く処理を行わないので
	// このような形で削除を行う
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		// イテレータが指す要素のオブジェクトを破棄
		delete *iter;
		// erase の戻り値は配列から除去した要素の次の要素を指すイテレータ!
		iter = mUIStack.erase(iter);
	}

	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::UnloadAllActors()
{
	// デストラクタで mActors から自分自身を取り除く処理を行うので
	// このような形で削除を行う
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

Font* Game::GetFont(const std::string& fileName)
{
	auto iter = mFonts.find(fileName);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}