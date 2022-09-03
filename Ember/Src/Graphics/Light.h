#pragma once
#include "../Math/glm.hpp"

struct LightColor
{
	glm::vec3 m_amb;
	glm::vec3 m_diff;
	glm::vec3 m_spec;
};

struct DirectionalLight
{
	LightColor m_color;
	glm::vec3 m_dir;
};

struct PointLight
{
	LightColor m_color;
	glm::vec3 m_pos;
};
