#pragma once

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	 Shader(const char* vertFilePath, const char* fragFilePath);
	~Shader();

	void Use() const;
	void Unuse() const;
	void SetBool(const char* uniform, const bool b);
	void SetInt(const char* uniform, const int i);
	void SetUint(const char* uniform, const unsigned int i);
	void SetFloat(const char* uniform, const float f);
	void SetVec3(const char* uniform, const glm::vec3& vec);
	void SetVec4(const char* uniform, const glm::vec4& vec);
	void SetMat3(const char* uniform, const glm::mat3& mat);
	void SetMat4(const char* uniform, const glm::mat4& mat);

private:
	GLuint m_ProgramID;

private:
	std::string ReadInSingleFile(const char* filePath);
	void AddToProgram(GLenum shaderType, const char* shaderSource);
	GLuint CompileShader(GLenum type, const char* source);
};

