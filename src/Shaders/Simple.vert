#version 330

in vec3 inPosition;

uniform mat4 model;
uniform mat4 view_proj;

void main() {
	gl_Position = view_proj * model * vec4(inPosition, 1.0);
	//gl_Position = vec4(inPosition, 1.0);
}