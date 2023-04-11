#pragma once

#include "RayTracerSkybox.h"
#include "RayTracerRectangle.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "QuadricSurface.h"
#include <vector>

namespace graphics
{
	class RayTracerScene
	{
	public:
		RayTracerScene();
		void addRayTraceShader(const std::vector<std::string>& textureFiles, const char* vertexShader = "raytrace.vert", const char* fragmentShader = "raytrace.frag");
		Light& addLight(const Light& light);
		QuadricSurface& addQuadricSurface(const QuadricSurface& surface);
		void draw(const Camera& camera) const;
	private:
		std::unique_ptr<RayTracerRectangle> screen;
		glutils::Shader* shader;
		std::unique_ptr<glutils::TextureCubemap> skybox;
		std::vector<Light> lights;
		std::vector<QuadricSurface> surfaces;
	};
}