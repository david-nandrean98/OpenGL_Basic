#include "Skybox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace graphics
{
	Skybox::Skybox(const std::vector<std::string>& textureFiles, const char* vertexShader, const char* fragmentShader): mesh(), texture(textureFiles), shader(vertexShader, fragmentShader) {}
	Skybox::Skybox(Skybox&& other): mesh(std::move(other.mesh)), texture(std::move(other.texture)), shader(std::move(other.shader)) {}
	void Skybox::draw(const Camera& camera) const
	{
		glDepthFunc(GL_LEQUAL);
		shader.Use();
		const auto view = glm::mat4(glm::mat3(camera.ViewMatrix()));
		shader.setUniformMat4x4f("camMatrix", camera.ProjectionMatrix() * view);
		texture.Bind();
		mesh.draw();
		glDepthFunc(GL_LESS);
	}
}