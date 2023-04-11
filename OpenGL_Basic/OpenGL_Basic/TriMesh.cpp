#include "TriMesh.h"

namespace graphics
{

	TriMesh::TriMesh(const std::vector<Vertex>& vert, const std::vector<GLuint>& ind) :
		Mesh(static_cast<GLsizei>(ind.size()))
	{
		vao.Bind();
		vbo.initialize(vert.data(), vert.size() * sizeof(Vertex), GL_STATIC_DRAW);

		ebo.initialize(ind.data(), ind.size() * sizeof(GLuint), GL_STATIC_DRAW);

		vao.VertexAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)0);
		vao.VertexAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
		vao.VertexAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
		vao.VertexAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)(9 * sizeof(float)));

		glutils::VertexArrayObject::Unbind();
		glutils::VertexBufferObject::Unbind();
		glutils::ElementBufferObject::Unbind();
	}

	TriMesh::TriMesh(TriMesh&& other): Mesh(std::move(other)) {}

	void TriMesh::draw() const
	{
		vao.Bind();
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glutils::VertexArrayObject::Unbind();
	}
}