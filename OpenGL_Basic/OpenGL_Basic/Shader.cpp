#include "Shader.h"
#include "FileManipulation.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

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
		compileErrors(vertexShaderID, "VERTEX_SHADER");


		const auto fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShaderID);
		compileErrors(vertexShaderID, "FRAGMENT_SHADER");

		ID = glCreateProgram();

		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);

		glLinkProgram(ID);
		compileErrors(ID, "PROGRAM");

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	Shader::Shader(Shader&& other): ID(other.ID)
	{
		other.ID = 0;
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

	void Shader::setUniform1i(const char* name, const int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name), value);
	}

	void Shader::compileErrors(unsigned int shader, const char* type)
	{
		// Stores status of compilation
		GLint hasCompiled;
		// Character array to store error message in
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				//glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
			else
			{
				std::cout << "Shader has compiled successfully" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			int length;
			glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length);
			std::string infolog(static_cast<size_t>(length), 0);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, &infolog[0]);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << "length = " << length <<  infolog << std::endl;
			}
			else
			{
				std::cout << "PROGRAM has linked successfully" << std::endl;
			}
		}
	}
}