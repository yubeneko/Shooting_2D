#pragma once

#include "UIComponent.h"

class UIImage : public UIComponent
{
public:
	UIImage(
		class Texture* texture,
		class UIScreen* owner,
		const glm::vec2& position = glm::vec2(0.0f, 0.0f),
		float scale = 1.0f,
		float rotation = 0.0f,
		const std::string& name = "UIImage Component");

	// UIButton と同様、このクラスにも破棄するリソースは存在しないので
	// デストラクタは不要

protected:
	void DrawTexture(class Shader* shader) override;

private:
	class Texture* mTexture;
};