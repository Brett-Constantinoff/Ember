#pragma once
#include <vector>
#include "../Math/glm.hpp"

struct Material
{
	const char* m_shader;
	const char* m_texture;
	std::vector<const char*> m_skybox;
	glm::vec3 m_diff;
	glm::vec3 m_amb;
	glm::vec3 m_spec;
	float m_shine;

	//nomral material
	Material(
		const char* shader,
		const char* texture,
		glm::vec3 diff = { 1.0f, 1.0f, 1.0f },
		glm::vec3 m_amb = { 0.1f, 0.1f, 0.1f },
		glm::vec3 spec = { 1.0f, 1.0f, 1.0f },
		float shine = 5.0f
	);

	//skybox maertial
	Material(const char* shader, std::vector<const char*> skybox);
};