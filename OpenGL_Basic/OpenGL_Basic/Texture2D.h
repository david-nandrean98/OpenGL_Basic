#pragma once

#include "Texture.h"

namespace glutils
{
	class Texture2D: public Texture
	{
	public:
		Texture2D(const char* imagePath, const GLenum slot, const GLenum format, const GLenum pixelFormat);
		Texture2D(const Texture2D& other) = delete;
		Texture2D(Texture2D&& other);
		void Bind() const override;
		static void Unbind();
	private:
		static const GLuint textureType = GL_TEXTURE_2D;
	};
}