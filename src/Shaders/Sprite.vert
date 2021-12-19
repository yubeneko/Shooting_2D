#version 330

layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexCoord;

uniform mat4 uModel;
uniform mat4 uViewProj;

out vec2 fragTexCoord;

void main() {
	gl_Position = uViewProj * uModel * vec4(inPosition, 1.0);
	fragTexCoord = inTexCoord;
}