#pragma once
#include <vector>
#include "../Math/glm.hpp"

struct MaterialProps
{
	const char* shader;
	const char* m_texture;
	glm::vec3 m_diff = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_amb = { 1.0f, 0.5f, 0.31f };
	glm::vec3 m_spec = { 0.5f, 0.5f, 0.5f };
	float m_shine = 32.0f;
};

struct Material
{
	//nomral material
	Material(MaterialProps props);

	//skybox maertial
	Material(std::vector<const char*> skybox);

	MaterialProps m_props;
	std::vector<const char*> m_skybox;
};