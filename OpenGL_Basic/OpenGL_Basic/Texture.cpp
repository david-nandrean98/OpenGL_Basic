#include "Texture.h"

namespace glutils
{
	Texture::Texture()
	{
		glGenTextures(1, &ID);
	}

	Texture::Texture(Texture&& other) : ID(other.ID)
	{
		other.ID = 0;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &ID);
	}
}