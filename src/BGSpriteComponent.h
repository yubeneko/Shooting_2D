#pragma once

#include "SpriteComponent.h"
#include <glm/glm.hpp>
#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;

	void SetBGTextures(const std::vector<Texture*>& textures);
	void SetScrollSpeed (float speed) { mScrollSpeed = speed; }

private:
	struct BGTexture
	{
		Texture* mTexture;
		glm::vec2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	float mScrollSpeed;
};