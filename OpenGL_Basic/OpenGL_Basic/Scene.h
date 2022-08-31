#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "graphics_utils.h"
#include <vector>

namespace graphics
{
	class Scene
	{
	public:
		Scene();
		void drawMeshes(const Camera& camera) const;
		Mesh& addMesh(const char* filename, const char* textureFile, const FileFormat3D format);
	private:
		std::vector<Mesh> meshes;
	};
}