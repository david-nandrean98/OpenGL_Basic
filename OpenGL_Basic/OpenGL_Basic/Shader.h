#pragma once

#include <glad/glad.h>

namespace glutils
{
	class Shader
	{
		Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName);
		~Shader();
		void Use() const;
	private:
		GLuint ID;
	};
}