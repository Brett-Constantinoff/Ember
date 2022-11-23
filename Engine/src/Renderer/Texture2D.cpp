#include "Texture2D.h"

namespace Ember
{
	namespace Renderer
	{
		Texture2D::Texture2D(uint32_t type, int32_t width, int32_t height) :
			Texture{ type, width, height }
		{
		}

		Texture2D::~Texture2D()
		{
		}

		void Texture2D::loadDepth()
		{
			bind();
			glTexImage2D(m_type, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			unbind();
		}
	}
}