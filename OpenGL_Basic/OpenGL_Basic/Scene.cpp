#include "Scene.h"

namespace graphics
{
	Scene::Scene() = default;

	void Scene::drawMeshes(Camera& camera)
	{
		for (auto& mesh : meshes)
		{
			mesh->draw(camera, lights);
		}
	}

	void Scene::addMesh(Camera& camera, const char* filename, const char* textureFile, const FileFormat3D format)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		switch (format)
		{
			case FileFormat3D::OBJ:MeshLoader::loadOBJ(filename, vertices, indices); break;
			default: throw std::runtime_error("Load function for this format is not implemented: " + std::string(ToString(format))); break;
		}

		meshes.push_back(std::make_unique<Mesh>(camera, lights, vertices, indices, "default.vert", "default.frag", textureFile));
	}

	void Scene::addMesh(Camera& camera, const std::vector<Vertex>& vert, const std::vector<GLuint>& ind, const char* vertShader, const char* fragmentShader, const char* textureFile)
	{
		meshes.push_back(std::make_unique<Mesh>(camera, lights, vert, ind, vertShader, fragmentShader, textureFile));
	}
	void Scene::addSphere(Camera& camera)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		ParametricSurfaceConstructor::construct(50, &ParametricSurfaceConstructor::Sphere, vertices, indices);


		meshes.push_back(std::make_unique<Mesh>(camera, lights, vertices, indices, "default.vert", "default.frag", "brick.png"));
	}
	void Scene::addLight(const Light& light)
	{
		lights.push_back(light);
	}
}