#pragma once
#include <stdint.h>
#include <vector>
#include "../Math/glm.hpp"
#include "../Math/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

enum class Primitive
{
	QUAD = 0,
	CUBE = 1,
};

struct Geometry
{
	std::vector<float> m_vertexPos;
	std::vector<uint32_t> m_indices;
	//add other vertex info here
	//things like normals etc

	//filepath will be for custom meshes
	Geometry(Primitive type, const char* filePath = nullptr);
};

struct Material
{
	const char* m_shader;
	glm::vec3 m_diff;
	glm::vec3 m_amb;
	glm::vec3 m_spec;
	float m_shine;
};


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
	IndexBuffer* m_ibo = nullptr;

	glm::vec3 m_pos = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };
	glm::mat4 m_rotation = glm::mat4(1.0f);
	float m_rotAngle = 0.0f;

};