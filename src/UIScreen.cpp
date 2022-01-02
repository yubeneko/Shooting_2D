#include "UIScreen.h"
#include "Game.h"
#include "Renderer.h"
#include "UIComponent.h"
#include <algorithm>

UIScreen::UIScreen(Game* game)
  : mGame(game),
	mState(EActive)
{
	// UIスタックに追加
	game->PushUI(this);
}

UIScreen::~UIScreen()
{
	// UIコンポーネントを全部破棄する
	// UIComponent のデストラクタで mUIComponents から自分自身を
	// 取り除く処理を行う
	while (!mUIComponents.empty())
	{
		delete mUIComponents.back();
	}
}

void UIScreen::ProcessInput(const struct InputState& state)
{
	for (auto ui : mUIComponents)
	{
		ui->ProcessInput(state);
	}
	UIScreenInput(state);
}

void UIScreen::UIScreenInput(const struct InputState& state)
{
}

void UIScreen::Update(float deltaTime)
{
	// 保持するUIコンポーネントの更新
	for (auto ui : mUIComponents)
	{
		ui->Update(deltaTime);
	}

	// UIスクリーン自身の更新をする
	UpdateUIScreen(deltaTime);
}

void UIScreen::UpdateUIScreen(float deltaTime)
{
}

void UIScreen::Draw(Shader* shader)
{
	// UIコンポーネントを描画していく
	for (auto ui : mUIComponents)
	{
		ui->DrawTexture(shader);
	}
}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::AddUIComponent(UIComponent* uiComp)
{
	mUIComponents.emplace_back(uiComp);
}

void UIScreen::RemoveUIComponent(UIComponent* uiComp)
{
	auto iter = std::find(mUIComponents.begin(), mUIComponents.end(), uiComp);
	if (iter != mUIComponents.end())
	{
		mUIComponents.erase(iter);
	}
}