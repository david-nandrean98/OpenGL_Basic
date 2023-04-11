#pragma once

#include <glad/glad.h>
#include <stb/stb_images.h>
#include <stdexcept>

namespace glutils
{
	class Texture
	{
	public:
		Texture();
		Texture(const Texture& other) = delete;
		Texture(Texture&& other);
		~Texture();
		virtual void Bind() const = 0;

	protected:
		GLuint ID;
	};
}