#pragma once
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(std::string& name, std::string& shader);
	~Cube();

private:
	VertexBuffer m_colorBuffer;
};