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

class Mesh
{
public:
	Mesh(Geometry geo, Material mat);
	~Mesh();

	void updateUniforms(glm::mat4 proj, glm::mat4 view);
	void render();
	void translate(glm::vec3 translation);
	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 axis);

private:
	Geometry m_geo;
	Material m_mat;
	Shader* m_shader;

	VertexArray* m_vao;
	VertexBuffer* m_posBuffer;
	VertexBuffer* m_uvBuffer;
	IndexBuffer* m_ibo = nullptr;
	Texture* m_texture2D;
	Texture* m_textureSkybox;
	bool m_enableTexture = false;
	bool m_enableSkybox = false;

	glm::vec3 m_pos = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };
	glm::mat4 m_rotation = glm::mat4(1.0f);
	glm::mat4 m_model;
	float m_rotAngle = 0.0f;
};