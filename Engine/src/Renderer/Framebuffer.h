#pragma once
#include "Buffer.h"
#include "Texture2D.h"

namespace Ember
{
	namespace Renderer
	{
		class Framebuffer : public Buffer
		{
		public:
			Framebuffer(uint32_t type);
			virtual ~Framebuffer();

			virtual void bind();
			virtual void unbind();
			virtual void generate();
			void attachDepthTex(Texture2D* depthTex);
			Texture2D getDepthTex();
			bool notComplete();

		private:
			Texture2D* m_depthTex;
		};
	}
}