#pragma once

#include <glm/glm.hpp>

// RGBの順のカラー(0~1の範囲)
namespace Color
{
	static const glm::vec3 Black(0.0f, 0.0f, 0.0f);
	static const glm::vec3 White(1.0f, 1.0f, 1.0f);
	static const glm::vec3 Red(1.0f, 0.0f, 0.0f);
	static const glm::vec3 Green(0.0f, 1.0f, 0.0f);
	static const glm::vec3 Blue(0.0f, 0.0f, 1.0f);
}  // namespace Color