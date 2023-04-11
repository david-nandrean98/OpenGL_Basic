#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <string>

namespace graphics
{
	struct Material
	{
		Material(const glm::vec3& ambient = glm::vec3(0.0f), const glm::vec3& diffuse = glm::vec3(0.0f), const glm::vec3& specular = glm::vec3(0.0f), const float shininess = 0.0f);

		// Source: http://devernay.free.fr/cours/opengl/materials.html
		static Material Emerald();
		static Material Jade();
		static Material Obsidian();
		static Material Pearl();
		static Material Ruby();
		static Material Turquoise();
		static Material Brass();
		static Material Bronze();
		static Material Chrome();
		static Material Copper();
		static Material Gold();
		static Material Silver();
		static Material BlackPlastic();
		static Material CyanPlastic();
		static Material GreenPlastic();
		static Material RedPlastic();
		static Material WhitePlastic();
		static Material YellowPlastic();
		static Material BlackRubber();
		static Material CyanRubber();
		static Material GreenRubber();
		static Material RedRubber();
		static Material WhiteRubber();
		static Material YellowRubber();
		
		void setUniform(const glutils::Shader& shader, const std::string& variable) const;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}
