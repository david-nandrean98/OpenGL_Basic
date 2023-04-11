#pragma once

#include "Skybox.h"

namespace graphics
{
	class RayTracerSkybox : public Skybox
	{
	public:
		RayTracerSkybox(const std::vector<std::string>& textureFiles, const char* vertexShader, const char* fragmentShader);
		RayTracerSkybox(const RayTracerSkybox& other) = delete;
		RayTracerSkybox(RayTracerSkybox&& other);
		void draw(const Camera& camera) const override;
	};
}
