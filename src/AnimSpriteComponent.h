#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <glm/glm.hpp>

class AnimSpriteComponent : public SpriteComponent
{
public:
	// テクスチャを切り替えてアニメーションを行う場合のコンストラクタ
	// コンストラクタを呼び出した後で SetAnimTextures を呼び出すことでテクスチャをセットする
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// テクスチャアトラスを利用し、UV座標を切り替えることでアニメーションを行う場合のコンストラクタ
	AnimSpriteComponent(class Texture* texture, int row, int col, class Actor* owner, int drawOrder = 100);
	void Update(float deltaTime) override;
	void Draw(class Shader* shader, class VertexArray* vao) override;

	void SetAnimTextures(const std::vector<Texture*>& textures);
	float GetAnimFPS () const { return mAnimFPS; }
	void SetAnimFPS (float fps) { mAnimFPS = fps; }

private:
	float mCurrentFrame;
	float mAnimFPS;

	// テクスチャアトラスを使わない場合は、テクスチャを複数枚用意して、
	// そのテクスチャを切り替えることでアニメーションを行う
	std::vector<Texture*> mAnimTextures;

	// 画像領域の幅
	float mImageAreaWidth;
	// 画像領域の高さ
	float mImageAreaHeight;
	// uv座標における幅
	float mUVWidth;
	// uv座標における高さ
	float mUVHeight;
	// 現在表示に使うUV座標値
	glm::vec2 mCurrentUV;
	// UV座標の配列(アニメーションの順番で表示)
	std::vector<glm::vec2> mUVs;

	// テクスチャアトラスを使っているかどうか
	bool mIsUsingTextureAtlas;
};