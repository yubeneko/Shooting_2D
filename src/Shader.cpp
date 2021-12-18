#include "Shader.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <SDL.h>

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vShaderFileName, const std::string& fShaderFileName)
{
	if (!CompileShader(vShaderFileName, GL_VERTEX_SHADER, mVertShaderID) ||
		!CompileShader(fShaderFileName, GL_FRAGMENT_SHADER, mFragShaderID))
	{
		return false;
	}

	mShaderProgramID = glCreateProgram();
	glAttachShader(mShaderProgramID, mVertShaderID);
	glAttachShader(mShaderProgramID, mFragShaderID);
	glLinkProgram(mShaderProgramID);

	if (!IsValidProgram(mShaderProgramID)) { return false; }

	return true;
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgramID);
	glDeleteShader(mVertShaderID);
	glDeleteShader(mFragShaderID);
}

void Shader::SetActive() { glUseProgram(mShaderProgramID); }

void Shader::SetMatrixUniform(const char* name, const float* matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgramID, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream ifs(fileName);
	if (!ifs)
	{
		SDL_Log("Shader file not found : %s", fileName.c_str());
		return false;
	}

	std::ostringstream oss;
	oss << ifs.rdbuf();
	std::string contents = oss.str();
	const char* contentsChar = contents.c_str();

	outShader = glCreateShader(shaderType);
	glShaderSource(outShader, 1, &(contentsChar), nullptr);
	glCompileShader(outShader);

	if (!IsCompiled(outShader))
	{
		SDL_Log("Failed to compile Shader : %s", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram(const GLuint programID)
{
	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(programID, 511, nullptr, buffer);
		std::string message(buffer);
		SDL_Log("GLSL Link status:\n%s", buffer);
		return false;
	}

	return true;
}