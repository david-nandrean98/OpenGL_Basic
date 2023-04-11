#pragma once

#include "Material.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <string>

namespace graphics
{
	class QuadricSurface
	{
	public:
		enum Type
		{
			Diffuse = 0,
			Reflective,
			Refractive

		};
		QuadricSurface(const glm::mat4& surface, const Type type = Type::Diffuse, const Material& material = Material());
		void rotate(const float angle, const glm::vec3& axis);
		void scale(const glm::vec3& factor);
		void scale(const float factor);
		void translate(const glm::vec3& translation);
		void setUniform(const glutils::Shader& shader, const std::string& variable) const;
	private:
		glm::mat4 surface;
		glm::mat4 model;
		Material material;
		Type type;

	};
}