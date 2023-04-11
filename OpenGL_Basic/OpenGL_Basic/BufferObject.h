#pragma once

#include "VertexObject.h"
#include <memory>


namespace glutils
{
	template<GLenum target>
	class BufferObject : public VertexObject
	{
	public:
		BufferObject() = default;

		BufferObject(const BufferObject& other) = delete;

		BufferObject(BufferObject&& other) : VertexObject(std::move(other))
		{
		}

		void initialize(const void* data, const GLsizeiptr size, const GLenum usage)
		{
			glGenBuffers(1, &ID);
			glBindBuffer(target, ID);
			glBufferData(target, size, data, usage);
		}

		~BufferObject()
		{
			glDeleteBuffers(1, &ID);
		}

		void Bind() const override
		{
			glBindBuffer(target, ID);
		}

		static void Unbind()
		{
			glBindBuffer(target, 0);
		}
	};

	using VertexBufferObject = BufferObject<GL_ARRAY_BUFFER>;
	using ElementBufferObject = BufferObject<GL_ELEMENT_ARRAY_BUFFER>;
}