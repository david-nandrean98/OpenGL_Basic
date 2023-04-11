#pragma once

#include "SkyboxMesh.h"
#include "TextureCubemap.h"
#include "Shader.h"
#include "Camera.h"

namespace graphics
{
	class Skybox
	{
	public:
		Skybox(const std::vector<std::string>& textureFiles, const char* vertexShader, const char* fragmentShader);
		Skybox(const Skybox& other) = delete;
		Skybox(Skybox&& other);
		virtual void draw(const Camera& camera) const;
	protected:
		SkyboxMesh mesh;
		glutils::TextureCubemap texture;
		glutils::Shader shader;
	};
}
