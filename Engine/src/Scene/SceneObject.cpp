#include "SceneObject.h"

SceneObject::SceneObject(const char* name, const Material& material, const Transformation& transformation) :
	m_name{ name }, m_mat{ material }, m_trans{ transformation }, m_vbo {GL_ARRAY_BUFFER}, m_vao{}
{
}

SceneObject::SceneObject(const char* name, const Material& material) :
	m_name{ name }, m_mat{ material }, m_vbo{ GL_ARRAY_BUFFER }, m_vao{}
{
}

SceneObject::~SceneObject()
{
}

Material* SceneObject::getMaterial()
{
	return &m_mat;
}

Transformation* SceneObject::getTransform()
{
	return &m_trans;
}

VertexArray* SceneObject::getVao()
{
	return &m_vao;
}

VertexBuffer* SceneObject::getVbo()
{
	return &m_vbo;
}
