#include "Mesh.h"

Geometry::Geometry(Primitive type, const char* filePath)
{
	if (type == Primitive::QUAD)
	{
		m_vertexPos = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
		};
		m_indices = {
			 0, 1, 2,
			 2, 3, 0
		};
	}

	else if (type == Primitive::CUBE)
	{
		m_vertexPos = {
			0.0f, 0.0f, 0.0f,       
			1.0f, 0.0f, 0.0f,       
			1.0f, 1.0f, 0.0f,       
			0.0f, 1.0f, 0.0f,       

			1.0f, 0.0f, 0.0f,       
			1.0f, 0.0f, 1.0f,       
			1.0f, 1.0f, 1.0f,       
			1.0f, 1.0f, 0.0f,       

			0.0f, 0.0f, 1.0f,       
			0.0f, 1.0f, 1.0f,       
			1.0f, 1.0f, 1.0f,       
			1.0f, 0.0f, 1.0f,       

			0.0f, 0.0f, 0.0f,       
			0.0f, 1.0f, 0.0f,       
			0.0f, 1.0f, 1.0f,       
			0.0f, 0.0f, 1.0f,       

			0.0f, 1.0f, 0.0f,       
			1.0f, 1.0f, 0.0f,       
			0.0f, 1.0f, 1.0f,       
			1.0f, 1.0f, 1.0f,       

			0.0f, 0.0f, 1.0f,       
			0.0f, 1.0f, 1.0f,       
			1.0f, 1.0f, 1.0f,       
			1.0f, 0.0f, 1.0f,       
		};
		m_indices = {
			0,  1,  2,      0,  2,  3,
			4,  5,  6,      4,  6,  7,
			8,  9,  10,     8,  10, 11,
			12, 13, 14,     12, 14, 15,
			16, 17, 18,     17, 18, 19,
			20, 21, 22,     21, 22, 23
		};
	}
}

Mesh::Mesh(Geometry geo, Material mat) :
	m_geo{ geo }, m_mat{ mat }
{

	m_vao = new VertexArray();
	m_posBuffer = new VertexBuffer(m_geo.m_vertexPos.size() * sizeof(float), &m_geo.m_vertexPos[0], GL_STATIC_DRAW);
	m_vao->enableAttrib(0, 3, sizeof(float) * 3, (void*)0);

	if (m_geo.m_indices.size() >= 0)
	{
		m_ibo = new IndexBuffer(m_geo.m_indices.size() * sizeof(uint32_t), sizeof(m_geo.m_indices), &m_geo.m_indices[0], GL_STATIC_DRAW);
	}

	m_shader = new Shader(m_mat.m_shader);
}

Mesh::~Mesh()
{
	delete m_vao;
	delete m_posBuffer;
	delete m_ibo;
	delete m_shader;
}

void Mesh::updateUniforms(glm::mat4 proj, glm::mat4 view)
{
	m_shader->use();
	m_shader->setVec3("uColor", m_mat.m_diff);
	m_shader->setMat4("uProjection", proj);
	m_shader->setMat4("uView", view);
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_pos);
	model *= m_rotation;
	model = glm::scale(model, m_scale);

	m_shader->setMat4("uModel", model);
}

void Mesh::render()
{
	m_vao->bind();
	if (m_ibo != nullptr)
	{
		m_ibo->draw();
	}
	m_vao->unBind();
}

void Mesh::translate(glm::vec3 translation)
{
	m_pos += translation;
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
	m_rotation = glm::rotate(m_rotation, glm::radians(angle), axis);
}

void Mesh::scale(glm::vec3 axis)
{
	m_scale *= axis;
}