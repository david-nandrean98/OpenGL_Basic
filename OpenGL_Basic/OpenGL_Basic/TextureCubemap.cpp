#include "TextureCubemap.h"
#include <cassert>

namespace glutils
{
	TextureCubemap::TextureCubemap(const std::vector<std::string>& textureFiles): Texture()
	{
		if (textureFiles.size() != 6)
		{
			throw std::runtime_error("The number of cubemap textures should be 6!");
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// These are very important to prevent seams
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (unsigned int i = 0; i < textureFiles.size(); i++)
		{
			stbi_set_flip_vertically_on_load(false);
			int width, height, nrChannels;
			unsigned char* data = stbi_load(textureFiles[i].c_str(), &width, &height, &nrChannels, 0);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);

		}
	}

	TextureCubemap::TextureCubemap(TextureCubemap&& other) noexcept: Texture(std::move(other)) {}

	void TextureCubemap::Bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	}

	void TextureCubemap::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}