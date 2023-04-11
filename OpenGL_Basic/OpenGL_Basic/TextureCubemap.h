#pragma once

#include "Texture.h"
#include <vector>

namespace glutils
{
	class TextureCubemap : public Texture
	{
	public:
		TextureCubemap(const std::vector<std::string>& textureFiles);
		TextureCubemap(const TextureCubemap& other) = delete;
		TextureCubemap(TextureCubemap&& other) noexcept;
		void Bind() const override;
		static void Unbind();
	private:
		static const GLuint textureType = GL_TEXTURE_CUBE_MAP;

	};
}