#include "Material.h"

Material::Material(const char* shader, const char* texture, glm::vec3 diff, glm::vec3 amb, glm::vec3 spec, float shine) :
	m_shader{ shader }, m_texture{ texture }, m_diff{ diff }, m_amb{ amb }, m_spec{ spec }, m_shine{ shine }
{
}

Material::Material(const char* shader, std::vector<const char*> files) :
	m_shader{ shader }, m_skybox{ files }
{
	m_texture = nullptr;
}