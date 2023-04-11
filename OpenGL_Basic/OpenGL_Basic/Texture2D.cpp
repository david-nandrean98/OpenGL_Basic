#include "Texture2D.h"
#include <memory>

namespace glutils
{
	Texture2D::Texture2D(const char* imagePath, const GLenum slot, const GLenum format, const GLenum pixelFormat): Texture()
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 0);

		glActiveTexture(slot);
		glBindTexture(textureType, ID);

		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelFormat, img);

		glGenerateMipmap(textureType);

		stbi_image_free(img);

		glBindTexture(textureType, 0);
	}
	Texture2D::Texture2D(Texture2D&& other) : Texture(std::move(other)) {}

	void Texture2D::Bind() const
	{
		glBindTexture(textureType, ID);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(textureType, 0);
	}
}