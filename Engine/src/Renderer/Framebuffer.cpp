#include "Framebuffer.h"

Framebuffer::Framebuffer(uint32_t type) :
	Buffer{type}
{
	generate();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_id);
}

void Framebuffer::bind()
{
	glBindFramebuffer(m_type, m_id);
}

void Framebuffer::unbind()
{
	glBindFramebuffer(m_type, 0);
}

void Framebuffer::generate()
{
	glGenFramebuffers(1, &m_id);
}

void Framebuffer::attachDepthTex(Texture& depthTex)
{
	bind();
	glFramebufferTexture2D(m_type, GL_DEPTH_ATTACHMENT, depthTex.getType(), depthTex.getId(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	unbind();
}