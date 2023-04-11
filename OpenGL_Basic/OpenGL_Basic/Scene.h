#pragma once

#include "TriMesh.h"
#include "DrawableObject.h"
#include "Skybox.h"
#include "Light.h"
#include "Camera.h"
#include "graphics_utils.h"
#include <vector>
#include <map>
#include <memory>

enum ParametricSurfaceChecker : uint8_t
{
	NONE = 0,
	SPHERE = 1 << 0,
	CYLINDER = 1 << 1
};

ParametricSurfaceChecker operator|(const ParametricSurfaceChecker lhs, const ParametricSurfaceChecker rhs);
ParametricSurfaceChecker operator&(const ParametricSurfaceChecker lhs, const ParametricSurfaceChecker rhs);


namespace graphics
{
	class Scene
	{
	public:
		Scene();
		void drawMeshes(const Camera& camera) const;
		void addMesh(const char* filename, const FileFormat3D format);
		void addMesh(const std::vector<Vertex>& vert, const std::vector<GLuint>& ind);
		void addShader(const char* vertShader, const char* fragmentShader);
		void addTexture(const char* textureFileName);
		void addSphere(const Camera& camera, const float radius = 1.0f, const size_t shader_index = 0, const size_t texture_index = 0);
		void addLight(const Light& light);
		void createSkybox(const std::vector<std::string>& textureFiles, const char* vertexShader = "skybox.vert", const char* fragmentShader = "skybox.frag");
		DrawableObject& getObject(const size_t index);
	private:
		std::unique_ptr<Skybox> skybox;
		std::vector<std::shared_ptr<TriMesh>> meshes;
		std::vector<DrawableObject> objects;
		std::map<ParametricSurfaceChecker, size_t> parametricMeshesMap;
		std::vector<Light> lights;
		ParametricSurfaceChecker psurf = ParametricSurfaceChecker::NONE;
		std::vector<std::shared_ptr<glutils::Shader>> shaders;
		std::vector<std::shared_ptr<glutils::Texture2D>> textures;
	};
}