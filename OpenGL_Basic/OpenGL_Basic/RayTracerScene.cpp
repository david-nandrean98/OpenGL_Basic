#include "RayTracerScene.h"

namespace graphics
{
	RayTracerScene::RayTracerScene() = default;;
	void RayTracerScene::addRayTraceShader(const std::vector<std::string>&textureFiles, const char* vertexShader, const char* fragmentShader)
	{
		screen = std::make_unique<RayTracerRectangle>();
		skybox = std::make_unique<glutils::TextureCubemap>(textureFiles);
		shader = new glutils::Shader(vertexShader, fragmentShader);
	}
	Light& RayTracerScene::addLight(const Light& light)
	{
		lights.push_back(light);
		return lights.back();
	}

	QuadricSurface& RayTracerScene::addQuadricSurface(const QuadricSurface& surface)
	{
		surfaces.push_back(surface);
		return surfaces.back();
	}

	void RayTracerScene::draw(const Camera& camera) const
	{
		shader->Use();
		skybox->Bind();
		shader->setUniform3f("cameraPos", camera.pos());
		shader->setUniformMat4x4f("rayDirMatrix", glm::inverse(camera.cameraMatrix()));

		// Set lights
		for (size_t i = 0; i < lights.size(); i++)
		{
			lights[i].setUniform(*shader, "lights[" + std::to_string(i) + "]");
		}
		shader->setUniform1i("lights_num", lights.size());

		// Set surfaces
		for (size_t i = 0; i < surfaces.size(); i++)
		{
			surfaces[i].setUniform(*shader, "surfaces[" + std::to_string(i) + "]");
		}
		shader->setUniform1i("surfaces_num", surfaces.size());

		screen->draw();
	}
}