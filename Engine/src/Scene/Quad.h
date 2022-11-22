#include "SceneObject.h"

namespace Ember
{
	namespace Scene
	{
		class Quad : public SceneObject
		{
		public:
			Quad(const char* name, Renderer::Material& material, Renderer::Transformation& transform);
			~Quad();
		};
	}
}