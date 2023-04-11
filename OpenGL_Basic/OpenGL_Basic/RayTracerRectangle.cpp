#include "RayTracerRectangle.h"

namespace graphics
{
	RayTracerRectangle::RayTracerRectangle() :Mesh(6)
	{
		/*

		  3                 2
	      -------------------
		  |                 |
		  |                 |
		  |                 |
		  |                 |
		  -------------------
		  0                  1

		*/

		GLfloat rectangleVertices[] =
		{
		   -1.0f, -1.0f,
			1.0f, -1.0f,
			1.0f,  1.0f,
		   -1.0f, 1.0f
		};


		GLuint rectangleIndices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		vao.Bind();
		vbo.initialize(rectangleVertices, sizeof(rectangleVertices), GL_STATIC_DRAW);
		ebo.initialize(rectangleIndices, sizeof(rectangleIndices), GL_STATIC_DRAW);
		vao.VertexAttribute(vbo, 0, 2, GL_FLOAT, 2 * sizeof(GLfloat), (GLvoid*)0);

		glutils::VertexArrayObject::Unbind();
		glutils::VertexBufferObject::Unbind();
		glutils::ElementBufferObject::Unbind();
	}

	RayTracerRectangle::RayTracerRectangle(RayTracerRectangle&& other): Mesh(std::move(other)) {}

	void RayTracerRectangle::draw() const
	{
		vao.Bind();
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glutils::VertexArrayObject::Unbind();
	}
}