#include "Scene.h"

namespace graphics
{
	Scene::Scene() = default;

	void Scene::drawMeshes(const Camera& camera) const
	{
		for (const auto& mesh : meshes)
		{
			mesh.draw(camera);
		}
	}

	Mesh& Scene::addMesh(const char* filename, const char* textureFile, const FileFormat3D format)
	{
		switch (format)
		{
			case FileFormat3D::OBJ: meshes.push_back(MeshLoader::loadOBJ(filename, textureFile)); break;
			default: throw std::runtime_error("Load function for this format is not implemented: " + std::string(ToString(format))); break;
		}

		return meshes.back();
	}
}