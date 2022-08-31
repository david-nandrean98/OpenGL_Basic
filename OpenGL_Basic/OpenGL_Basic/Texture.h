#pragma once

#include <glad/glad.h>
#include <stb/stb_images.h>
#include <stdexcept>

namespace glutils
{
	template<GLenum textureType>
	class Texture
	{
	public:
		Texture(const char* imagePath, const GLenum slot, const GLenum format, const GLenum pixelFormat)
		{
			stbi_set_flip_vertically_on_load(true);

			int width, height, channels;
			unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 0);

			glGenTextures(1, &ID);
			glActiveTexture(slot);

			glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

			switch (textureType)
			{
				case GL_TEXTURE_2D: glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelFormat, img); break;
				default: throw std::runtime_error("No implementation for this texture type!"); break;
			}
			glGenerateMipmap(textureType);

			stbi_image_free(img);

			glBindTexture(textureType, 0);
		}

		~Texture()
		{
			glDeleteTextures(1, &ID);
		}

		void Bind() const
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(textureType, ID);
		}

		static void Unbind()
		{
			glBindTexture(textureType, 0);
		}

	private:
		GLuint ID;
	};

	using Texture2D = Texture<GL_TEXTURE_2D>;
}