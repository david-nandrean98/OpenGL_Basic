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

glm::vec3 Light::getPosition() const
{
	return position;
}

glm::vec3 Light::getColor() const
{
	return color;
}
