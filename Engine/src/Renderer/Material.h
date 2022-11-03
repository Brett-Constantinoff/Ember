#pragma once
#include "Shader.h"
#include "../../math/glm/glm.hpp"

struct Material
{
public:
	Material(glm::vec3 diff, glm::vec3 amb, glm::vec3 spec, float shine, const char* shader) :
		m_diff{ diff }, m_amb{ amb }, m_spec{ spec }, m_shine{ shine }, m_shader{ shader }
	{
	}

public:
	glm::vec3 m_diff;
	glm::vec3 m_amb;
	glm::vec3 m_spec;
	float m_shine;
	Shader m_shader;
};