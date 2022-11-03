#include "SceneObject.h"

SceneObject::SceneObject(const char* name, Material material) :
	m_name{ name }, m_mat{ material }, m_vbo{ GL_ARRAY_BUFFER }, m_vao{}, m_model{ glm::mat4(1.0f) }
{
}

SceneObject::~SceneObject()
{
}

Material* SceneObject::getMaterial()
{
	return &m_mat;
}

VertexArray* SceneObject::getVao()
{
	return &m_vao;
}

VertexBuffer* SceneObject::getVbo()
{
	return &m_vbo;
}

glm::mat4* SceneObject::getModel()
{
	return &m_model;
}

void SceneObject::setModel(glm::mat4& model)
{
	m_model = model;
}