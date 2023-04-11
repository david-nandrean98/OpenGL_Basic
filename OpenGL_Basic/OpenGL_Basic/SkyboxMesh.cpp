#include "SkyboxMesh.h"

namespace graphics
{
	SkyboxMesh::SkyboxMesh(): Mesh(36)
	{

		GLfloat skyboxVertices[] =
		{
			// Source: https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%2019%20-%20Cubemaps%20%26%20Skyboxes/Main.cpp
			//   Coordinates
			-1.0f, -1.0f,  1.0f,//        7--------6
			 1.0f, -1.0f,  1.0f,//       /|       /|
			 1.0f, -1.0f, -1.0f,//      4--------5 |
			-1.0f, -1.0f, -1.0f,//      | |      | |
			-1.0f,  1.0f,  1.0f,//      | 3------|-2
			 1.0f,  1.0f,  1.0f,//      |/       |/
			 1.0f,  1.0f, -1.0f,//      0--------1
			-1.0f,  1.0f, -1.0f
		};

		GLuint skyboxIndices[] =
		{
			// Right
			1, 2, 6,
			6, 5, 1,
			// Left
			0, 4, 7,
			7, 3, 0,
			// Top
			4, 5, 6,
			6, 7, 4,
			// Bottom
			0, 3, 2,
			2, 1, 0,
			// Back
			0, 1, 5,
			5, 4, 0,
			// Front
			3, 7, 6,
			6, 2, 3
		};

		vao.Bind();
		vbo.initialize(skyboxVertices, sizeof(skyboxVertices), GL_STATIC_DRAW);
		ebo.initialize(skyboxIndices, sizeof(skyboxIndices), GL_STATIC_DRAW);
		vao.VertexAttribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (GLvoid*)0);

		glutils::VertexArrayObject::Unbind();
		glutils::VertexBufferObject::Unbind();
		glutils::ElementBufferObject::Unbind();
	}

	SkyboxMesh::SkyboxMesh(SkyboxMesh&& other): Mesh(std::move(other)) {}

	void SkyboxMesh::draw() const
	{
		vao.Bind();
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glutils::VertexArrayObject::Unbind();
	}
}
