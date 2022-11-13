#pragma once
#include "../../libs/math/glm/glm.hpp"
#include "../../libs/math/glm/gtc/matrix_transform.hpp"
#include "../../libs/math/glm/gtc/type_ptr.hpp"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Material.h"
#include "../Renderer/Transformation.h"
#include <string>

class SceneObject
{
public:
	SceneObject(const char* name, const Material& material, const Transformation& transformation);
	SceneObject(const char* name, const Material& material);
	~SceneObject();

	Material* getMaterial();
	Transformation* getTransform();
	VertexBuffer* getVbo();
	VertexArray* getVao();

	void rotate(float angle, glm::vec3& axis);

protected:
	const char* m_name;
	VertexBuffer m_vbo;
	VertexArray m_vao;
	Material m_mat;
	Transformation m_trans;
};