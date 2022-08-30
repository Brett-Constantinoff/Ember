#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(size_t size, uint32_t count, void* data, int32_t mode, int32_t target) :
	m_target{target}, m_count{count}
{
	glGenBuffers(1, &m_id);
	bind();
	glBufferData(m_target, size, data, mode);
	unBind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind()
{
	glBindBuffer(m_target, m_id);
}

void VertexBuffer::unBind()
{
	glBindBuffer(m_target, m_id);
}

void VertexBuffer::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, m_count);
}
