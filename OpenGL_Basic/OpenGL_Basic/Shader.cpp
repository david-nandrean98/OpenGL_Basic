#include "Shader.h"
#include "FileManipulation.h"
#include <glm/gtc/type_ptr.hpp>

namespace glutils
{
	Shader::Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName)
	{

		const auto vertexCode = core::getFileContents(vertexShaderFileName);
		const auto fragmentCode = core::getFileContents(fragmentShaderFileName);

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		const auto vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
		glCompileShader(vertexShaderID);

		const auto fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShaderID);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(ID);
	}

	void Shader::Use() const
	{
		glUseProgram(ID);
	}

	void Shader::setUniform1f(const char* name, const GLfloat value) const
	{
		glUniform1f(glGetUniformLocation(ID, name), value);
	}

	void Shader::setUniform2f(const char* name, const glm::vec2& value) const
	{
		glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
	}

	void Shader::setUniform3f(const char* name, const glm::vec3& value) const
	{
		glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
	}

	void Shader::setUniform4f(const char* name, const glm::vec4& value) const
	{
		glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniformMat4x4f(const char* name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
	}
}