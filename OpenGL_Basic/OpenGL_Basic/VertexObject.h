#pragma once

#include <glad/glad.h>

namespace glutils
{
	class VertexObject
	{
	public:
		VertexObject() = default;
		VertexObject(const VertexObject& other) = delete;
		VertexObject(VertexObject&& other) : ID(other.ID)
		{
			other.ID = 0;
		}
		virtual void Bind() const = 0;
	protected:
		GLuint ID;
	};
}