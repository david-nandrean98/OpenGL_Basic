#pragma once

#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <vector>

namespace graphics
{
	class Camera;

	class Mesh
	{
	public:
		Mesh(const std::vector<GLfloat>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile);
		void draw(const Camera& camera) const;

	protected:
		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		glutils::VertexArrayObject vao;
		glutils::VertexBufferObject vbo;
		glutils::ElementBufferObject ebo;
		glutils::Shader shader;
		glutils::Texture2D texture;
		glm::mat4 model;
	};
}