#pragma once
#include "SceneObject.h"

namespace Ember
{
	namespace Scene
	{
		class Cube : public SceneObject
		{
		public:
			Cube(const char* name, const Renderer::Material & material, const Renderer::Transformation& transformation);
			~Cube();
		};
	}
}