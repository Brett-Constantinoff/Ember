#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(const char* name, const char* shader);
	~Cube();

private:
	VertexBuffer m_colorBuffer;
};