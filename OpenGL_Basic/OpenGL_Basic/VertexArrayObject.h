#pragma once

#include "VertexObject.h"
#include "BufferObject.h"

namespace glutils
{

	class VertexArrayObject : public VertexObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		void Bind() const override;
		static void Unbind();
		static void VertexAttribute(const VertexBufferObject& vbo, const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* pointer);
	};
}