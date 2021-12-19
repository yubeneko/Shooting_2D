#version 330

in vec3 inPosition;

uniform mat4 uModel;
uniform mat4 uViewProj;

void main() {
	gl_Position = uViewProj * uModel * vec4(inPosition, 1.0);
}