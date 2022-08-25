#include "Shader.h"
#include "FileManipulation.h"

namespace glutils
{
	Shader::Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName)
	{
		const char* vertexSource = core::getFileContents(vertexShaderFileName).c_str();
		const char* fragmentSource = core::getFileContents(fragmentShaderFileName).c_str();

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
}