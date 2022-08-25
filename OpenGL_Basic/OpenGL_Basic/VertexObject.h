#pragma once

#include <glad/glad.h>

namespace glutils
{
	class VertexObject
	{
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	protected:
		GLuint ID;
	};
}