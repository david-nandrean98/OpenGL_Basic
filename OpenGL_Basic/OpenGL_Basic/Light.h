#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <string>

class Light
{
public:
	enum class LightType
	{
		Directional = 0,
		Spotlight
	};
	Light(const LightType type, const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f));
	Light(const Light& other);
	LightType getType() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	void setUniform(const glutils::Shader& shader, const std::string& variable) const;
private:
	LightType type;
	glm::vec3 position;
	glm::vec3 color;
};
