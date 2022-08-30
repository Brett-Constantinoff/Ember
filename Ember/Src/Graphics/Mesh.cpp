#include "Mesh.h"

Mesh::Mesh(Geometry geo, Material mat) :
	m_geo{ geo }, m_mat{ mat }
{
	m_vao = new VertexArray();
	m_posBuffer = new VertexBuffer(m_geo.m_vertexPos.size() * sizeof(float), m_geo.m_vertexPos.size() / 3, & m_geo.m_vertexPos[0], GL_STATIC_DRAW);
	m_vao->enableAttrib(0, 3, sizeof(float) * 3, (void*)0);

	if (m_geo.m_indices.size() > 0)
	{
		m_ibo = new IndexBuffer(m_geo.m_indices.size() * sizeof(uint32_t), sizeof(m_geo.m_indices), &m_geo.m_indices[0], GL_STATIC_DRAW);
	}

	if (m_mat.m_texture != nullptr)
	{
		m_uvBuffer = new VertexBuffer(m_geo.m_uvs.size() * sizeof(float), m_geo.m_uvs.size() / 2, & m_geo.m_uvs[0], GL_STATIC_DRAW);
		m_vao->enableAttrib(1, 2, sizeof(float) * 2, (void*)0);
		m_texture2D = new Texture();
		m_texture2D->load2D(m_mat.m_texture);
		m_enableTexture = true;
	}

	if (m_mat.m_skybox.size() == 6)
	{
		m_textureSkybox = new Texture(true);
		m_textureSkybox->loadSkybox(m_mat.m_skybox);
		m_enableSkybox = true;
	}

	m_shader = new Shader(m_mat.m_shader);
}

Mesh::~Mesh()
{
	delete m_vao;
	delete m_posBuffer;
	delete m_uvBuffer;
	delete m_ibo;
	delete m_texture2D;
	delete m_textureSkybox;
	delete m_shader;
}

void Mesh::updateUniforms(glm::mat4 proj, glm::mat4 view)
{
	m_shader->use();

	if (m_enableSkybox)
	{
		m_shader->setMat4("uProjection", proj);
		m_shader->setMat4("uView", view);
		m_shader->setInt("uSkybox", 0);
	}
	else
	{
		m_shader->setVec3("uColor", m_mat.m_diff);
		m_shader->setMat4("uProjection", proj);
		m_shader->setMat4("uView", view);
		if (m_enableTexture)
		{
			m_shader->setInt("uTexture", 0);
			m_shader->setInt("uEnableTexture", m_enableTexture);
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_pos);
		model *= m_rotation;
		model = glm::scale(model, m_scale);
		m_model = model;

		m_shader->setMat4("uModel", m_model);
	}
}

void Mesh::render()
{
	if (m_enableTexture)
	{
		m_texture2D->active(0);
		m_texture2D->bind();
	}
	if (m_enableSkybox)
	{
		m_textureSkybox->active(0);
		m_textureSkybox->bind();
	}

	m_vao->bind();
	if (m_ibo != nullptr)
	{
		m_ibo->draw();
	}
	else
	{
		m_posBuffer->draw();
	}
	m_vao->unBind();

	if (m_enableTexture)
	{
		m_texture2D->unBind();
	}
	if (m_enableSkybox)
	{
		m_textureSkybox->unBind();
	}
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
