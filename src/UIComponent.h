#pragma once

#include <string>
#include <glm/glm.hpp>

/**
 * @brief UIComponent クラス
 * UIText や UIButton といったUIパーツクラスの基底クラスとなる。
 * UIScreen クラスにぶら下がる形をとる。
 */
class UIComponent
{
public:
	UIComponent(
		class UIScreen* owner,
		const glm::vec2& position = glm::vec2(0.0f, 0.0f),
		float scale = 1.0f,
		float rotation = 0.0f,
		const std::string& name = "UIComponent");
	virtual ~UIComponent();

	virtual void ProcessInput(const struct InputState& state);
	void Update(float deltaTime);
	virtual void UpdateUIComponent(float deltaTime);

	// Getter/Setter
	std::string GetName() const { return mName; }
	void SetName(const std::string& name) { mName = name; }

	glm::vec2 GetPosition() const { return mPosition; }
	void SetPosition(const glm::vec2& position)
	{
		mShouldRecomputeModelMat = true;
		mPosition = position;
	}

	float GetScale() const { return mScale; }
	void SetScale(float scale)
	{
		mShouldRecomputeModelMat = true;
		mScale = scale;
	}

	float GetRotation() const { return mRotation; }
	// ラジアンで渡す
	void SetRotation(float rotation)
	{
		mShouldRecomputeModelMat = true;
		mRotation = rotation;
	}

protected:
	// UIScreen だけが DrawTexture メソッドにアクセスできるようにする
	friend class UIScreen;
	virtual void DrawTexture(class Shader* shader) = 0;

private:
	void ComputeModelMatrix();

protected:
	class UIScreen* mOwnerScreen;
	glm::mat4 GetModelMat() const { return mModelMat; }

private:
	// 座標
	glm::vec2 mPosition;
	// スケール
	float mScale;
	// 回転(ラジアン)
	float mRotation;
	// UIパーツオブジェクトの名前(開発用途)
	std::string mName;
	// モデル行列
	glm::mat4 mModelMat;
	// モデル行列を再計算する必要があるかどうか
	bool mShouldRecomputeModelMat;
};