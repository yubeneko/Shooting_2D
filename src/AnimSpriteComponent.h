#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <glm/glm.hpp>

class AnimSpriteComponent : public SpriteComponent
{
public:
	/**
	 * @brief テクスチャを切り替えてアニメーションを行う場合のコンストラクタ
	 * コンストラクタを呼び出した後で SetAnimTextures を呼び出すことでテクスチャをセットする
	 *
	 * @param owner オーナーのアクター
	 * @param drawOrder 描画順(若いほど先に描画される)
	 */
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	/**
	 * @brief テクスチャアトラスを利用し、UV座標を切り替えることでアニメーションを行う場合のコンストラクタ
	 * テクスチャアトラスの中の各画像は全て同一サイズであることを想定。
	 *
	 * @param texture テクスチャ
	 * @param row テクスチャアトラスの行数
	 * @param col テクスチャアトラスの列数
	 * @param owner オーナーのアクター
	 * @param drawOrder 描画順(若いほど先に描画される)
	 */
	AnimSpriteComponent(class Texture* texture, int row, int col, class Actor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;
	void Draw(class Shader* shader, class VertexArray* vao) override;

	/**
	 * @brief テクスチャを切り替えてアニメーションを行う場合に使うメンバ関数。
	 *
	 * @param textures アニメーションで利用するテクスチャの配列
	 */
	void SetAnimTextures(const std::vector<Texture*>& textures);

	/**
	 * @brief テクスチャアトラスによりアニメーションを行う場合に使うメンバ関数
	 *
	 * @param texture テクスチャ
	 * @param row テクスチャアトラスの行数
	 * @param col テクスチャアトラスの列数Ï
	 */
	void SetTextureAtlas(class Texture* texture, int row, int col);

	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	bool GetIsLooping() const { return mIsLooping; }
	void SetIsLooping(bool isloop) { mIsLooping = isloop; }
	bool GetIsPlaying() const { return mIsPlaying; }
	void SetIsPlaying(bool isPlay) { mIsPlaying = isPlay; }

private:
	float mCurrentFrame;
	float mAnimFPS;
	bool mIsLooping;
	bool mIsPlaying;

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