#include "UIImage.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

UIImage::UIImage(
	Texture* texture,
	UIScreen* owner,
	const glm::vec2& position,
	float scale,
	float rotation,
	const std::string& name)
  : UIComponent(owner, position, scale, rotation, name),
	mTexture(texture)
{
}

void UIImage::DrawTexture(Shader* shader)
{
	// 短形をテクスチャの幅と高さで拡大する
	glm::mat4 scale = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(
			static_cast<float>(mTexture->GetWidth()),
			static_cast<float>(mTexture->GetHeight()),
			1.0f));
	glm::mat4 model = GetModelMat() * scale;
	shader->SetMatrixUniform("uModel", glm::value_ptr(model));
	mTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}