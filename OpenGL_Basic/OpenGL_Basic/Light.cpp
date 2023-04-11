#include "Light.h"

Light::Light(const LightType t, const glm::vec3& pos, const glm::vec3& col): type(t), position(pos), color(col)
{
	if (type == LightType::Directional)
	{
		position = glm::normalize(position);
	}
}

Light::Light(const Light& other): type(other.type), position(other.position), color(other.color) {}

Light::LightType Light::getType() const
{
	return type;
}

const glm::vec3& Light::getPosition() const
{
	return position;
}

const glm::vec3& Light::getColor() const
{
	return color;
}

void Light::setUniform(const glutils::Shader& shader, const std::string& variable) const
{
	shader.setUniform1i((variable + ".type").c_str(), static_cast<std::underlying_type<LightType>::type>(type));
	shader.setUniform3f((variable + ".position").c_str(), position);
	shader.setUniform3f((variable + ".color").c_str(), color);
}
