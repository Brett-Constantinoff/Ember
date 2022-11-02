#pragma once
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/Shader.h"
#include <string>

class SceneObject
{
public:
	SceneObject(std::string& name, std::string& shader);
	~SceneObject();

	Shader* getShader();
	VertexBuffer* getVbo();
	VertexArray* getVao();
	glm::mat4* getModel();
	void setModel(glm::mat4& model);

protected:
	std::string m_name;
	glm::mat4 m_model;
	Shader m_shader;
	VertexBuffer m_vbo;
	VertexArray m_vao;
};