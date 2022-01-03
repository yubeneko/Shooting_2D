#pragma once

#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader, class VertexArray* vao);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

protected:
	class Texture* mTexture;
	// デフォルトの頂点バッファをセットする
	void SetDefaultVertexBuffer(class VertexArray* vao);

private:
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};