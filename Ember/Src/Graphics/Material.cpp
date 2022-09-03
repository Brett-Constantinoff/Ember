#include "Material.h"

Material::Material(MaterialProps props) :
	m_props{props}
{
}

Material::Material(std::vector<const char*> files) :
	m_skybox{ files }
{
	m_props.shader = ".\\Src\\Shaders\\skyboxShader.hlsl";
	m_props.m_texture = nullptr;
}