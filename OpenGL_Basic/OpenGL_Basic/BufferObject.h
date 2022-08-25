#pragma once

#include "VertexObject.h"


namespace glutils
{
	template<GLenum target>
	class BufferObject : public VertexObject
	{
	public:
		BufferObject(const GLfloat* vertices, const GLsizeiptr size, const GLenum usage)
		{
			glGenBuffers(1, &ID);
			glBindBuffer(target, ID);
			glBufferData(target, size, vertices, usage);
		}

		~BufferObject()
		{
			glDeleteBuffers(1, &ID);
		}

		void Bind() const override
		{
			glBindBuffer(target, ID);
		}

		void Unbind() const override
		{
			glBindBuffer(target, 0);
		}
	};

	using VertexBufferObject = BufferObject<GL_ARRAY_BUFFER>;
	using ElementBufferObject = BufferObject<GL_ELEMENT_ARRAY_BUFFER>;
}