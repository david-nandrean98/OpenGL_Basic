#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Light.h"
#include "Camera.h"
#include <vector>

namespace graphics
{
	class DrawableObject
	{
	public:
		DrawableObject(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<glutils::Shader>& shader, const std::shared_ptr<glutils::Texture2D>& texture);
		void rotate(const float angle, const glm::vec3& axis);
		void scale(const glm::vec3& factor);
		void scale(const float factor);
		void translate(const glm::vec3& translation);
		void draw(const Camera& camera, const std::vector<Light>& lights) const;
	private:
		void useLights(const std::vector<Light>& lights) const;
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<glutils::Shader> shader;
		std::shared_ptr<glutils::Texture2D> texture;
		glm::mat4 model;
	};
}
