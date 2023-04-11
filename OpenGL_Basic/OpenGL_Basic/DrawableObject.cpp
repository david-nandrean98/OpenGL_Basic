#include "DrawableObject.h"
#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <string>

namespace graphics
{
	DrawableObject::DrawableObject(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<glutils::Shader>& shader, const std::shared_ptr<glutils::Texture2D>& texture):
		mesh(mesh), shader(shader), texture(texture), model{1.0f}
	{
	}

	void DrawableObject::rotate(const float angle, const glm::vec3& axis)
	{
		model = glm::rotate(model, angle, axis);
	}

	void DrawableObject::scale(const glm::vec3& factor)
	{
		model = glm::scale(model, factor);
	}

	void DrawableObject::scale(const float factor)
	{
		model = glm::scale(model, glm::vec3(factor));
	}
	void DrawableObject::translate(const glm::vec3& translation)
	{
		model = glm::translate(model, translation);
	}

	void DrawableObject::draw(const Camera& camera, const std::vector<Light>& lights) const
	{
		shader->Use();
		texture->Bind();
		shader->setUniformMat4x4f("model", model);
		shader->setUniform3f("cameraPosition", camera.pos());
		shader->setUniformMat4x4f("cameraMatrix", camera.cameraMatrix());
		useLights(lights);
		mesh->draw();
	}

	void DrawableObject::useLights(const std::vector<Light>& lights) const
	{
		assert(lights.size() <= 5);

		for (size_t i = 0; i < lights.size(); ++i)
		{
			const auto variable = "lights[" + std::to_string(i) + "].";
			shader->setUniform1i((variable + "type").c_str(), static_cast<std::underlying_type<Light::LightType>::type>(lights[i].getType()));
			shader->setUniform3f((variable + "position").c_str(), lights[i].getPosition());
			shader->setUniform3f((variable + "color").c_str(), lights[i].getColor());
		}

		for (size_t i = lights.size(); i < 5; ++i)
		{
			const auto variable = "lights[" + std::to_string(i) + "].";
			shader->setUniform1i((variable + "type").c_str(), 0);
			shader->setUniform3f((variable + "position").c_str(), glm::vec3(0.0f));
			shader->setUniform3f((variable + "color").c_str(), glm::vec3(0.0f));
		}

		shader->setUniform1i("light_num", lights.size());
	}
}