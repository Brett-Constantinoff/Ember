#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Utilities/stb_image.h"

Texture::Texture(bool cubeMap)
{
	glGenTextures(1, &m_id);
	if (cubeMap)
	{
		m_type = GL_TEXTURE_CUBE_MAP;
		bind();
		glTexParameteri(m_type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
	else
	{
		m_type = GL_TEXTURE_2D;
		bind();
	}
	glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::active(uint32_t index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Texture::bind(void)
{
	glBindTexture(m_type, m_id);
}

void Texture::unBind(void)
{
	glBindTexture(m_type, 0);
}

void Texture::load2D(const char* file)
{
	int32_t width;
	int32_t height;
	int32_t channels;

	uint8_t* data = stbi_load(file, &width, &height, &channels, 0);
	if (data)
	{
		uint32_t format;
		if (channels == 1)
		{
			format = GL_RED;
		}
		else if (channels == 3)
		{
			format = GL_RGB;
		}
		else if (channels == 4)
		{
			format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << file << std::endl;
	}	
	stbi_image_free(data);
}

void Texture::loadSkybox(std::vector<const char*> files)
{
	int32_t width;
	int32_t height;
	int32_t channels;

	for (int32_t i = 0; i < files.size(); i++)
	{
		uint8_t* data = stbi_load(files[i], &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << files[i] << std::endl;
			stbi_image_free(data);
		}
	}
}