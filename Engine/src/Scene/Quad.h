#include "SceneObject.h"

class Quad : public SceneObject
{
public:
	Quad(const char* name, Material& material, Transformation& transform);
	~Quad();
};