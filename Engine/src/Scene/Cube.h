#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(const char* name, Material material);
	~Cube();
};