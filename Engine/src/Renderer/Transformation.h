#pragma once

#include "../../libs/math/glm/glm.hpp"

struct Transformation
{
public:
	Transformation(){};
	Transformation(glm::vec3 translation, glm::vec3 scale, glm::mat4 rotation) :
		m_translation{ translation }, m_scale{ scale }, m_rotation{ rotation }
	{
	}
	~Transformation()
	{
	}

public:
	glm::vec3 m_translation;
	glm::vec3 m_scale;
	glm::mat4 m_rotation;
};