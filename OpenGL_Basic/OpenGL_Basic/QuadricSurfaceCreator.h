#pragma once

#include <glm/glm.hpp>

namespace graphics
{
	struct QuadricSurfaceCreator
	{
		static glm::mat4 Sphere();
		static glm::mat4 Ellipsoid(const float x, const float y, const float z);
		static glm::mat4 Plane();
		static glm::mat4 Cylinder(const float a, const float b);
		static glm::mat4 Hyberboloid();
	};
}
