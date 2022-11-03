#pragma once
#include "../../libs/math/glm/glm.hpp"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/Shader.h"
#include <string>

class SceneObject
{
public:
	SceneObject(const char* name, const char* shader);
	~SceneObject();

	Shader* getShader();
	VertexBuffer* getVbo();
	VertexArray* getVao();
	glm::mat4* getModel();
	void setModel(glm::mat4& model);

protected:
	const char* m_name;
	glm::mat4 m_model;
	Shader m_shader;
	VertexBuffer m_vbo;
	VertexArray m_vao;
};