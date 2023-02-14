#pragma once

#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "graphics_utils.h"
#include <vector>
#include <memory>

namespace graphics
{
	class Scene
	{
	public:
		Scene();
		void drawMeshes(Camera& camera);
		void addMesh(Camera& camera, const char* filename, const char* textureFile, const FileFormat3D format);
		void addMesh(Camera& camera, const std::vector<Vertex>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile);
		void addSphere(Camera& camera);
		void addLight(const Light& light);
	private:
		std::vector<std::unique_ptr<Mesh>> meshes;
		std::vector<Light> lights;
	};
}