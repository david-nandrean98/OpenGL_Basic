#pragma once

#include "VertexObject.h"

namespace glutils
{
	class VertexBufferObject;

	class VertexArrayObject : public VertexObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		void Bind() const override;
		void Unbind() const override;
		static void VertexAttribute(const VertexBufferObject& vbo, const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* pointer);
	};
}