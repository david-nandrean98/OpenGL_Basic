#pragma once

#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "Shader.h"
#include "Texture.h"
#include "Light.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace graphics
{
	struct Vertex
	{
		Vertex(const glm::vec3& p = glm::vec3(0.0f), const glm::vec3& n = glm::vec3(0.0f), const glm::vec3& c = glm::vec3(1.0f, 1.0f, 1.0f)):
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

	class Camera;

	class Mesh
	{
	public:
		Mesh(Camera& camera, const std::vector<Light>& lights, const std::vector<Vertex>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile);
		void draw(Camera& camera, const std::vector<Light>& lights);
		void useLights(const std::vector<Light>& lights);

	private:
		GLsizei size;
		glutils::VertexArrayObject vao;
		glutils::VertexBufferObject vbo;
		glutils::ElementBufferObject ebo;
		glutils::Shader shader;
		glutils::Texture2D texture;
		glm::mat4 model;
	};
}