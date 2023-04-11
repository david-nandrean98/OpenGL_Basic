#pragma once

#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include <glm/glm.hpp>

namespace graphics
{

	struct Vertex
	{
		Vertex(const glm::vec3& p = glm::vec3(0.0f), const glm::vec3& n = glm::vec3(0.0f), const glm::vec3& c = glm::vec3(1.0f, 1.0f, 1.0f)) :
			position(p), normal(n), color(c) {}
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texCoord;
		bool operator==(const Vertex& other)
		{
			return position == other.position && normal == other.normal && color == other.color && texCoord == other.texCoord;
		}
	};

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other): vao(std::move(other.vao)), vbo(std::move(other.vbo)), ebo(std::move(other.ebo)) {}
		Mesh(const GLsizei size): size(size) {}
		virtual void draw() const = 0;

	protected:
		GLsizei size;
		glutils::VertexArrayObject vao;
		glutils::VertexBufferObject vbo;
		glutils::ElementBufferObject ebo;
	};
}
