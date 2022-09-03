#include "Mesh.h"

Mesh::Mesh(Geometry geo, Material mat) :
	m_geo{ geo }, m_mat{ mat }
{
	m_vao = new VertexArray();
	m_posBuffer = new VertexBuffer(m_geo.m_vertexPos.size() * sizeof(float), m_geo.m_vertexPos.size() / 3, &m_geo.m_vertexPos[0], GL_STATIC_DRAW);
	m_vao->enableAttrib(3, sizeof(float) * 3, (void*)0); //location 0

	if (m_geo.m_vertexNorm.size() > 0)
	{
		m_normalBuffer = new VertexBuffer(m_geo.m_vertexNorm.size() * sizeof(float), m_geo.m_vertexNorm.size() / 3, &m_geo.m_vertexNorm[0], GL_STATIC_DRAW);
		m_vao->enableAttrib(3, sizeof(float) * 3, (void*)0); //location 1
	}

	if (m_mat.m_props.m_texture != nullptr)
	{
		m_uvBuffer = new VertexBuffer(m_geo.m_uvs.size() * sizeof(float), m_geo.m_uvs.size() / 2, &m_geo.m_uvs[0], GL_STATIC_DRAW);
		m_vao->enableAttrib(2, sizeof(float) * 2, (void*)0); //location 2
		m_texture2D = new Texture();
		m_texture2D->load2D(m_mat.m_props.m_texture);
		m_enableTexture = true;
	}

	if (m_geo.m_indices.size() > 0)
	{
		m_ibo = new IndexBuffer(m_geo.m_indices.size() * sizeof(uint32_t), m_geo.m_indices.size(), &m_geo.m_indices[0], GL_STATIC_DRAW);
	}

	if (m_mat.m_skybox.size() == 6)
	{
		m_textureSkybox = new Texture(true);
		m_textureSkybox->loadSkybox(m_mat.m_skybox);
	}

	m_shader = new Shader(m_mat.m_props.shader);
}

Mesh::~Mesh()
{
	delete m_vao;
	delete m_posBuffer;
	delete m_normalBuffer;
	delete m_uvBuffer;
	delete m_ibo;
	delete m_texture2D;
	delete m_textureSkybox;
	delete m_shader;
}

bool Mesh::hasTexture(void)
{
	return m_enableTexture;
}

Material* Mesh::getMaterial(void)
{
	return &m_mat;
}

Texture* Mesh::getTexture(void)
{
	return m_texture2D;
}

Texture* Mesh::getSkyboxTexture(void)
{
	return m_textureSkybox;
}

Shader* Mesh::getShader(void)
{
	return m_shader;
}

TransformationInfo* Mesh::getTransforms(void)
{
	return &m_transforms;
}

VertexArray* Mesh::getVao(void)
{
	return m_vao;
}

VertexBuffer* Mesh::getVbo(void)
{
	return m_posBuffer;
}

IndexBuffer* Mesh::getIbo(void)
{
	return m_ibo;
}

void Mesh::translate(glm::vec3 translation)
{
	m_transforms.m_pos += translation;
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
	m_transforms.m_rotation = glm::rotate(m_transforms.m_rotation, glm::radians(angle), axis);
}

void Mesh::scale(glm::vec3 axis)
{
	m_transforms.m_scale *= axis;
}
