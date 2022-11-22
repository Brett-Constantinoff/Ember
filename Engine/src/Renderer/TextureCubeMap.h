#pragma once
#include <iostream>
#include <vector>
#include "Texture.h"
#include "../../libs/stb/stb_image.h"

namespace Ember
{
	namespace Renderer
	{
		class TextureCubeMap : public Texture
		{
		public:
			TextureCubeMap(uint32_t m_type, std::vector<const char*>& files);
			~TextureCubeMap();

			virtual void load();

		private:
			std::vector<const char*> m_files;
		};
	}
}