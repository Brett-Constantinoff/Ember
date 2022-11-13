#include "Texture.h"

Texture::Texture(uint32_t type) :
	m_type{ type }, m_width{0}, m_height{0}
{
	glGenTextures(1, &m_id);
}

Texture::Texture(uint32_t type, int32_t width, int32_t height) :
	m_type{ type }, m_width{ width }, m_height{ height }
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

uint32_t Texture::getId()
{
	return m_id;
}

uint32_t Texture::getType()
{
	return m_type;
}