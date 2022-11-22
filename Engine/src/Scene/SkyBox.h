#pragma once
#include <vector>
#include "../Renderer/Material.h"
#include "../Renderer/TextureCubeMap.h"
#include "SceneObject.h"

namespace Ember
{
	namespace Scene
	{
		class SkyBox : public SceneObject
		{
		public:
			SkyBox(const char* name, const Renderer::Material& material, std::vector<const char*>& files);
			~SkyBox();
			Renderer::TextureCubeMap* getCubeMap();

		private:
			Renderer::TextureCubeMap m_texture;
		};
	}
}