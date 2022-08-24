#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
	bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::enableAttrib(uint32_t index, uint32_t components, GLsizei stride, void* first, int type, int normalized)
{
	glVertexAttribPointer(index, components, type, normalized, stride, first);
	glEnableVertexAttribArray(index);
}

void VertexArray::bind()
{
	glBindVertexArray(m_id);
}

void VertexArray::unBind()
{
	glBindVertexArray(0);
}