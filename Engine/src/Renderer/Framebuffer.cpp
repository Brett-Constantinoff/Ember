#include "Framebuffer.h"

namespace Ember
{
	namespace Renderer
	{
		Framebuffer::Framebuffer(uint32_t type) :
			Buffer{ type }, m_depthTex{ nullptr }
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

		void Framebuffer::attachDepthTex(Texture2D* depthTex)
		{
			m_depthTex = depthTex;
			m_depthTex->loadDepth();
			bind();
			glFramebufferTexture2D(m_type, GL_DEPTH_ATTACHMENT, m_depthTex->getType(), m_depthTex->getId(), 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			if (notComplete())
			{
				std::cout << "ERROR::SHADOW FRAMEBUFFER INCOMPELTE\n";
			}
			unbind();
		}

		Texture2D Framebuffer::getDepthTex()
		{
			return *m_depthTex;
		}

		bool Framebuffer::notComplete()
		{
			return glCheckFramebufferStatus(m_type) != GL_FRAMEBUFFER_COMPLETE;
		}
	}
}