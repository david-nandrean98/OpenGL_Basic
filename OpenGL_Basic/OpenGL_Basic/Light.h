#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	enum LightType: int
	{
		Directional = 0,
		Spotlight
	};
	Light(const LightType type, const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f));
	Light(const Light& other);
	LightType getType() const;
	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
private:
	LightType type;
	glm::vec3 position;
	glm::vec3 color;
};
