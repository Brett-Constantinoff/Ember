#pragma once
#include "SceneObject.h"

SceneObject::SceneObject(std::string& name, std::string& shader) :
	m_name{ name }, m_shader{shader}, m_vbo{GL_ARRAY_BUFFER}, m_vao{}, m_model{glm::mat4(1.0f)}
{
}

SceneObject::~SceneObject()
{
}

Shader* SceneObject::getShader()
{
	return &m_shader;
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