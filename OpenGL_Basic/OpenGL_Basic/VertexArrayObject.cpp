#include "VertexArrayObject.h"
#include "BufferObject.h"

namespace glutils
{
	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &ID);
	}

	void VertexArrayObject::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VertexArrayObject::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArrayObject::VertexAttribute(const VertexBufferObject& vbo, const GLuint index, const GLint size, const GLenum type, const GLsizei stride, const GLvoid* pointer)
	{
		vbo.Bind();
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(index);
		vbo.Unbind();
	}
}