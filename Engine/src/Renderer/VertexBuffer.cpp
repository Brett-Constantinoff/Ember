#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(uint32_t type): Buffer(type)
{
}

void VertexBuffer::bind()
{
    glBindBuffer(m_bufferType, m_bufferId);
}

void VertexBuffer::unBind()
{
    glBindBuffer(m_bufferType, NULL);
}

void VertexBuffer::setData(size_t bytes, void* data, uint32_t usage)
{
    glBufferData(m_bufferType, bytes, data, usage);
}