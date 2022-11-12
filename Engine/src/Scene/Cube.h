#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(const char* name, const Material& material, const Transformation& transformation);
	~Cube();
};