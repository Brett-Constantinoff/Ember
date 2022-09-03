#pragma once
#include <stdint.h>
#include <vector>
#include <limits>
#include "../Math/glm.hpp"
#include "../Math/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Geometry.h"

struct TransformationInfo
{
	glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };
	glm::mat4 m_rotation = glm::mat4(1.0f);
	glm::mat4 m_model;
	float m_rotAngle = 0.0f;
};

class Mesh
{
public:
	Mesh(Geometry geo, Material mat);
	~Mesh();

	void translate(glm::vec3 translation);
	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 axis);

	bool hasTexture(void);
	Material* getMaterial(void);
	TransformationInfo* getTransforms(void);
	Texture* getTexture(void);
	Texture* getSkyboxTexture(void);
	Shader* getShader(void);
	VertexArray* getVao(void);
	VertexBuffer* getVbo(void);
	IndexBuffer* getIbo(void);

private:
	Geometry m_geo;
	Material m_mat;
	TransformationInfo m_transforms;

	VertexArray* m_vao;
	VertexBuffer* m_posBuffer;
	VertexBuffer* m_normalBuffer = nullptr;
	VertexBuffer* m_uvBuffer = nullptr;;
	IndexBuffer* m_ibo = nullptr;
	Texture* m_texture2D;
	Texture* m_textureSkybox;
	Shader* m_shader;
	bool m_enableTexture = false;
};