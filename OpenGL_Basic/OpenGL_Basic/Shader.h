#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace glutils
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		void initialize(const char* vertexShaderFileName, const char* fragmentShaderFileName);
		void Use();
		void setUniform1f(const char* name, const GLfloat value) const;
		void setUniform2f(const char* name, const glm::vec2& value) const;
		void setUniform3f(const char* name, const glm::vec3& value) const;
		void setUniform4f(const char* name, const glm::vec4& value) const;
		void setUniformMat4x4f(const char* name, const glm::mat4& value) const;
		void setUniform1i(const char* name, const int value) const;
		
	private:
		void compileErrors(unsigned int shader, const char* type);
		GLuint ID;
	};
}