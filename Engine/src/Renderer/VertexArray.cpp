#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

void VertexArray::bind()
{
    glBindVertexArray(m_id);
}
void VertexArray::unBind()
{
    glBindVertexArray(0);
}

void VertexArray::setLayout(uint32_t numPerAttrib, uint32_t type, uint32_t normalized, size_t stride, void* start)
{
    glVertexAttribPointer(m_layoutPos, numPerAttrib, type, normalized, stride, start);
    glEnableVertexAttribArray(m_layoutPos);
}