#pragma once

#include <string>
#include <glm/glm.hpp>

class UIComponent
{
public:
	UIComponent(
		class UIScreen* owner,
		const std::string& name,
		const glm::vec2& position = glm::vec2(0.0f, 0.0f),
		float scale = 1.0f,
		float rotation = 0.0f);
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
	// UIパーツオブジェクトの名前
	std::string mName;
	// 座標
	glm::vec2 mPosition;
	// スケール
	float mScale;
	// 回転(ラジアン)
	float mRotation;
	// モデル行列
	glm::mat4 mModelMat;
	// モデル行列を再計算する必要があるかどうか
	bool mShouldRecomputeModelMat;
};