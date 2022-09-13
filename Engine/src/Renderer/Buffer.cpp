#include "Buffer.h"

Buffer::Buffer(uint32_t type) :
	m_bufferType{type}
{
	glGenBuffers(1, &m_bufferId);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_bufferId);
}