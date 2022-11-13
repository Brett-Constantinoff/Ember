#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(uint32_t type): Buffer(type)
{
    generate();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind()
{
    glBindBuffer(m_type, m_id);
}

void VertexBuffer::unBind()
{
    glBindBuffer(m_type, NULL);
}

void VertexBuffer::generate()
{
    glGenBuffers(1, &m_id);
}

void VertexBuffer::setData(size_t bytes, void* data, uint32_t usage)
{
    glBufferData(m_type, bytes, data, usage);
}
