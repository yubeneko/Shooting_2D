#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const std::string& vShaderFileName, const std::string& fShaderFileName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const float* matrix);

private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram(const GLuint programID);

	GLuint mVertShaderID;
	GLuint mFragShaderID;
	GLuint mShaderProgramID;
};