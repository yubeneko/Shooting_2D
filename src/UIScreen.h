#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Color.h"

/**
 * @brief UIScreen クラス
 * ポーズメニューやゲームプレイ中のUIと言った、UIパーツを配置するキャンバスのような役割をもつクラス。
 * 新しくUI画面を作る時に派生させる。
 * UIComponent の派生クラスを保持し、それらに入力データを流したり更新処理を実行したり、描画処理を呼び出したりする
 *
 */
class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	void ProcessInput(const struct InputState& state);
	virtual void UIScreenInput(const struct InputState& state);

	void Update(float deltaTime);
	virtual void UpdateUIScreen(float deltaTime);

	void Draw(class Shader* shader);

	enum UIState
	{
		EActive,
		EClosing,
	};

	// UI画面を閉じる(閉じたUIは破棄される)
	void Close();

	UIState GetState() const { return mState; }
	class Game* GetGame() const { return mGame; }

	void AddUIComponent(class UIComponent* uiComp);
	void RemoveUIComponent(class UIComponent* uiComp);

protected:
	class Game* mGame;
	UIState mState;
	std::vector<class UIComponent*> mUIComponents;
};