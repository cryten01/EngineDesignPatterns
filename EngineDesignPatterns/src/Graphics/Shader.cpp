#include "Shader.h"


#include <fstream>
#include <string>
#include <vector>

Shader::Shader(const char* vertFilePath, const char* fragFilePath)
{
	m_ProgramID = glCreateProgram();

	std::string vertexSource = ReadInFile(vertFilePath);
	std::string fragmentSource = ReadInFile(fragFilePath);

	AddToProgram(GL_VERTEX_SHADER, vertexSource.c_str());
	AddToProgram(GL_FRAGMENT_SHADER, fragmentSource.c_str());

	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::Use() const
{
	glUseProgram(m_ProgramID);
}

void Shader::Unuse() const
{
	glUseProgram(0);
}

std::string Shader::ReadInFile(const char* filePath)
{
	std::string fileContent;
	std::ifstream fileStream(filePath, std::ios::in);

	assert(fileStream.is_open() && "Could not read file: {0}", filePath);

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		fileContent.append(line + "\n");
	}

	fileStream.close();
	return fileContent;
}

void Shader::AddToProgram(GLenum shaderType, const char* shaderSource)
{
	GLuint shaderID = CompileProgram(shaderType, shaderSource);
	glAttachShader(m_ProgramID, shaderID);
	glDeleteShader(shaderID);
}

GLuint Shader::CompileProgram(GLenum type, const char* source)
{
	// Necessary because OpenGL needs a raw string
	const char* shaderSource = source;

	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	/* ERROR HANDLING */
	GLint compiled;

	// Returns the compile status from the shader and stores it into compiled
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

	// OpenGL checks if the shader compile status is false
	if (compiled == GL_FALSE)
	{
		// Queries the error message length of the shader
		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		// Gets and prints the actual log
		std::vector<GLchar> errorMsg(length);
		glGetShaderInfoLog(shaderID, length, NULL, &errorMsg[0]);

		assert(false, errorMsg.data());
	}

	return shaderID;
}

void Shader::SetBool(const char* uniform, const bool b)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform1i(location, b);
}


void Shader::SetInt(const char* uniform, int i)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform1i(location, i);
}


void Shader::SetUint(const char* uniform, const unsigned int i)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform1ui(location, i);
}


void Shader::SetFloat(const char* uniform, const float f)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform1f(location, f);
}


void Shader::SetVec3(const char* uniform, const glm::vec3& vec)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform3fv(location, 1, &vec[0]);
}


void Shader::SetVec4(const char* uniform, const glm::vec4& vec)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniform4fv(location, 1, &vec[0]);
}


void Shader::SetMat3(const char* uniform, const glm::mat3& mat)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
}


void Shader::SetMat4(const char* uniform, const glm::mat4& mat)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}
