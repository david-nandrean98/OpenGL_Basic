#pragma once

#include <glad/glad.h>
#include <glm/common.hpp>
#include <cstdint>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>
#include <glm/glm.hpp>
#include "Mesh.h"

namespace graphics
{
	enum class FileFormat3D : uint8_t
	{
		STP,
		MAX,
		FBX,
		OBJ,
		X3D,
		VRML,
		DS3,
		MF3,
		STL,
		DAE
	};

	const char* ToString(const FileFormat3D format);

	struct MeshLoader
	{
		static void loadOBJ(const char* filename, /*out*/ std::vector<Vertex>& vertices, /*out*/ std::vector<GLuint>& indices);
	};

	struct ParametricSurfaceConstructor
	{
		static void construct(const int resolution, glm::vec3(*surface)(float, float), std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
		static void construct(const int resolution, glm::vec3(*surface)(float, float), glm::vec3(*normal)(float, float), std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
		struct Surface
		{
			static glm::vec3 Sphere(float u, float v);
			static glm::vec3 Cylinder(float u, float v);
		};
		struct Normal
		{
			static glm::vec3 Sphere(float u, float v);
		};
	};
}