#include "Mesh.h"
#include "Camera.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace graphics
{

	Mesh::Mesh(Camera& camera, const std::vector<Light>& lights, const std::vector<Vertex>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile) :
		size{static_cast<GLsizei>(ind.size())},
		texture{ textureFile, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE },
		model{ glm::mat4{1.0f} }
	{
		vao.Bind();
		vbo.initialize(vert.data(), vert.size() * sizeof(Vertex), GL_STATIC_DRAW);

		ebo.initialize(ind.data(), ind.size() * sizeof(GLuint), GL_STATIC_DRAW);
		shader.initialize(vertShader, fragmentShader);

		vao.VertexAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)0);
		vao.VertexAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
		vao.VertexAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
		vao.VertexAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)(9 * sizeof(float)));
		model = glm::mat4{ 5.0f };

		shader.Use();
		shader.setUniformMat4x4f("model", model);
		shader.setUniform3f("cameraPosition", camera.pos());
		shader.setUniformMat4x4f("cameraMatrix", camera.cameraMatrix());
		shader.setUniform1i("tex0", 0);
		useLights(lights);


		glutils::VertexArrayObject::Unbind();
		glutils::VertexBufferObject::Unbind();
		glutils::ElementBufferObject::Unbind();
		std::cout << "Created" << std::endl;

	}

	void Mesh::draw(Camera& camera, const std::vector<Light>& lights)
	{
		shader.Use();
		texture.Bind();
		vao.Bind();
		shader.setUniformMat4x4f("model", model);
		shader.setUniform3f("cameraPosition", camera.pos());
		shader.setUniformMat4x4f("cameraMatrix", camera.cameraMatrix());
		useLights(lights);
		std::cout << "gets called" << std::endl;
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glutils::VertexArrayObject::Unbind();
		std::cout << size << std::endl;
	}
	void Mesh::useLights(const std::vector<Light>& lights)
	{
		assert(lights.size() <= 5);

		for (size_t i = 0; i < lights.size(); ++i)
		{
			const auto variable = "lights[" + std::to_string(i) + "].";
			shader.setUniform1i((variable + "type").c_str(), lights[i].getType());
			shader.setUniform3f((variable + "position").c_str(), lights[i].getPosition());
			shader.setUniform3f((variable + "color").c_str(), lights[i].getColor());
		}

		for (size_t i = lights.size(); i < 5; ++i)
		{
			const auto variable = "lights[" + std::to_string(i) + "].";
			shader.setUniform1i((variable + "type").c_str(), 0);
			shader.setUniform3f((variable + "position").c_str(), glm::vec3(0.0f));
			shader.setUniform3f((variable + "color").c_str(), glm::vec3(0.0f));
		}

		shader.setUniform1i("light_num", lights.size());
	}
}