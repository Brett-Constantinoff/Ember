#pragma once
#include <GL/glew.h>
#include <stdint.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void enableAttrib(uint32_t components, GLsizei stride, void* first, int type = GL_FLOAT, int normalized = GL_FALSE);
	void bind();
	void unBind();

private:
	uint32_t m_id;
	uint32_t m_index = 0;
};