#include "QuadricSurface.h"
#include <glm/gtx/transform.hpp>

namespace graphics
{
	QuadricSurface::QuadricSurface(const glm::mat4& surface, const Type type, const Material& material) : surface(surface), model(1.0f), material(material), type(type)
	{
	}

	void QuadricSurface::rotate(const float angle, const glm::vec3& axis)
	{
		model = glm::rotate(model, angle, axis);
	}

	void QuadricSurface::scale(const float factor)
	{
		scale(glm::vec3(factor, factor, factor));
	}

	void QuadricSurface::scale(const glm::vec3& factor)
	{
		model = glm::scale(model, factor);
	}

	void QuadricSurface::translate(const glm::vec3& translation)
	{
		model = glm::translate(model, translation);
	}

	void QuadricSurface::setUniform(const glutils::Shader& shader, const std::string& variable) const
	{
		const auto modelInverse = glm::inverse(model);
		shader.setUniformMat4x4f((variable + ".surface").c_str(), glm::transpose(modelInverse) * surface * modelInverse);
		material.setUniform(shader, variable + ".material");
		shader.setUniform1i((variable + ".type").c_str(), type);
	}

}
