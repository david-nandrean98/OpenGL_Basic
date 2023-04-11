#include "RayTracerSkybox.h"

namespace graphics
{
	RayTracerSkybox::RayTracerSkybox(const std::vector<std::string>& textureFiles, const char* vertexShader, const char* fragmentShader) : Skybox(textureFiles, vertexShader, fragmentShader) {}
	RayTracerSkybox::RayTracerSkybox(RayTracerSkybox&& other) : Skybox(std::move(other)) {}
	void RayTracerSkybox::draw(const Camera& camera) const
	{
		glDepthFunc(GL_LEQUAL);
		shader.Use();
		const auto view = glm::mat4(glm::mat3(camera.ViewMatrix()));
		shader.setUniformMat4x4f("camMatrix", camera.ProjectionMatrix() * view);
		shader.setUniformMat4x4f("rayDirMatrix", glm::inverse(camera.ProjectionMatrix() * view));
		shader.setUniform3f("cameraPos", camera.pos());
		texture.Bind();
		mesh.draw();
		glDepthFunc(GL_LESS);
	}
}