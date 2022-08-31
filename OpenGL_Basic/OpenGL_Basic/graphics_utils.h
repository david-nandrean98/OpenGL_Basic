#pragma once

#include "Mesh.h"

#include <glad/glad.h>
#include <cstdint>
#include <vector>

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
		static Mesh loadOBJ(const char* filename, const char* textureFile);
	};
}