#include "Texture.h"

Texture::Texture(uint32_t type) :
	m_type{ type }
{
	glGenTextures(1, &m_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind()
{
	glBindTexture(m_type, m_id);
}

void Texture::unbind()
{
	glBindTexture(m_type, 0);
}