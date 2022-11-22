#pragma once
#include "../../libs/glad/include/glad/glad.h"
#include <stdint.h>
#include <cstring>

namespace Ember
{
	namespace Renderer
	{
		class Buffer
		{
		public:
			Buffer(uint32_t type);
			virtual ~Buffer() {};

			virtual void bind() {};
			virtual void unBind() {};
			virtual void generate() {};

		protected:
			uint32_t m_id;
			uint32_t m_type;
		};
	}
}