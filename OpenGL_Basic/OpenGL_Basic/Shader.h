#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace glutils
{
	class Shader
	{
	public:
		Shader(const char* vertexShaderFileName, const char* fragmentShaderFileName);
		~Shader();
		void Use() const;
		void setUniform1f(const char* name, const GLfloat value) const;
		void setUniform2f(const char* name, const glm::vec2& value) const;
		void setUniform3f(const char* name, const glm::vec3& value) const;
		void setUniform4f(const char* name, const glm::vec4& value) const;
		void setUniformMat4x4f(const char* name, const glm::mat4& value) const;
	private:
		GLuint ID;
	};
}