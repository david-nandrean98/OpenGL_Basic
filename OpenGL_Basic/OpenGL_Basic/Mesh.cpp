#include "Mesh.h"
#include "Camera.h"
#include <stdexcept>

namespace graphics
{
	Mesh::Mesh(const std::vector<GLfloat>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile) :
		vertices{vert},
		indices{ind},
		vao{},
		shader{vertShader, fragmentShader},
		texture{textureFile, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE},
		model{1.0f}
	{
		vao.Bind();
		vbo.initialize(vertices.data(), vertices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
		ebo.initialize(indices.data(), indices.size() * sizeof(GLuint), GL_STATIC_DRAW);

		vao.VertexAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)0);
		vao.VertexAttribute(vbo, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		vao.VertexAttribute(vbo, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	
		glutils::VertexArrayObject::Unbind();
		glutils::VertexBufferObject::Unbind();
		glutils::ElementBufferObject::Unbind();

		shader.Use();
		shader.setUniform1f("tex0", 0);
	}

	void Mesh::draw(const Camera& camera) const
	{
		shader.Use();
		shader.setUniform1f("tex0", 0);
		shader.setUniformMat4x4f("model", model);
		shader.setUniform3f("cameraPosition", camera.pos());
		shader.setUniformMat4x4f("cameraMatrix", camera.cameraMatrix());
		texture.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	}
}