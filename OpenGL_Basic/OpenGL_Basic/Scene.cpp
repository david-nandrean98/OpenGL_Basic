#include "Scene.h"
#include <cassert>

ParametricSurfaceChecker operator|(const ParametricSurfaceChecker lhs, const ParametricSurfaceChecker rhs)
{
	return static_cast<ParametricSurfaceChecker>(static_cast<std::underlying_type<ParametricSurfaceChecker>::type>(lhs) | static_cast<std::underlying_type<ParametricSurfaceChecker>::type>(rhs));
}
ParametricSurfaceChecker operator&(const ParametricSurfaceChecker lhs, const ParametricSurfaceChecker rhs)
{
	return static_cast<ParametricSurfaceChecker>(static_cast<std::underlying_type<ParametricSurfaceChecker>::type>(lhs) & static_cast<std::underlying_type<ParametricSurfaceChecker>::type>(rhs));
}

namespace graphics
{
	Scene::Scene() = default;

	void Scene::drawMeshes(const Camera& camera) const
	{
		for (const auto& object : objects)
		{
			object.draw(camera, lights);
		}

		skybox->draw(camera);
	}

	void Scene::addMesh(const char* filename, const FileFormat3D format)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		switch (format)
		{
			case FileFormat3D::OBJ:MeshLoader::loadOBJ(filename, vertices, indices); break;
			default: throw std::runtime_error("Load function for this format is not implemented: " + std::string(ToString(format))); break;
		}

		addMesh(vertices, indices);
	}

	void Scene::addMesh(const std::vector<Vertex>& vert, const std::vector<GLuint>& ind)
	{
		meshes.push_back(std::make_shared<TriMesh>(vert, ind));
	}

	void Scene::addShader(const char* vertShader, const char* fragmentShader)
	{
		shaders.push_back(std::make_shared<glutils::Shader>(vertShader, fragmentShader));
	}

	void Scene::addTexture(const char* textureFileName)
	{
		textures.push_back(std::make_shared<glutils::Texture2D>(textureFileName, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE));
	}

	void Scene::addSphere(const Camera& camera, const float radius, const size_t shader_index, const size_t texture_index)
	{
		if (psurf & ParametricSurfaceChecker::SPHERE)
		{
			objects.push_back(DrawableObject(meshes[parametricMeshesMap[ParametricSurfaceChecker::SPHERE]], shaders[shader_index], textures[texture_index]));
			objects.back().scale(radius);
		}
		else
		{
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			ParametricSurfaceConstructor::construct(50, &ParametricSurfaceConstructor::Surface::Sphere, &ParametricSurfaceConstructor::Normal::Sphere, vertices, indices);
			parametricMeshesMap.insert(std::make_pair(ParametricSurfaceChecker::SPHERE, meshes.size()));
			meshes.push_back(std::make_shared<TriMesh>(vertices, indices));
			psurf = psurf | ParametricSurfaceChecker::SPHERE;
			objects.push_back(DrawableObject(meshes.back(), shaders[shader_index], textures[texture_index]));
			objects.back().scale(radius);
		}
	}
	void Scene::addLight(const Light& light)
	{
		lights.push_back(light);
	}

	void Scene::createSkybox(const std::vector<std::string>& textureFiles, const char* vertexShader, const char* fragmentShader)
	{
		skybox = std::make_unique<Skybox>(textureFiles, vertexShader, fragmentShader);
	}

	DrawableObject& Scene::getObject(const size_t index)
	{
		return objects[index];
	}
}