#pragma once
#include <iostream>
#include <stdint.h>
#include "../../libs/glad/include/glad/glad.h"

namespace Ember
{
	namespace Renderer
	{
		class Texture
		{
		public:
			Texture(uint32_t type);
			Texture(uint32_t type, int32_t width, int32_t height);
			~Texture();

			void bind();
			void unbind();
			uint32_t getId();
			uint32_t getType();
			int32_t getWidth();
			int32_t getHeight();
			virtual void load() {};

		protected:
			uint32_t m_type;
			uint32_t m_id;
			int32_t m_width;
			int32_t m_height;
		};
	}
}