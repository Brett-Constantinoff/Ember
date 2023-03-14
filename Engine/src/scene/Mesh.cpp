#include "Mesh.h"
#include <iostream>

namespace Ember::Scene
{
	Mesh::Mesh(const RenderData& renderData) :
		 m_renderData{renderData}
	{
		initRenderData();
	}

	Mesh::~Mesh()
	{
		for (const auto& resource : m_renderData.m_resources)
			glDeleteBuffers(1, &resource);
		glDeleteVertexArrays(1, &m_renderData.m_vao);
	}

	RenderData& Mesh::getRenderData()
	{
		return m_renderData;
	}

	TransformData& Mesh::getTransformData()
	{
		return m_transformData;
	}

	void Mesh::initRenderData()
	{
		// positions
		glGenBuffers(1, &m_renderData.m_vbo);
		m_renderData.m_resources.push_back(m_renderData.m_vbo);

		// normals
		glGenBuffers(1, &m_renderData.m_nbo);
		m_renderData.m_resources.push_back(m_renderData.m_nbo);

		// indices
		glGenBuffers(1, &m_renderData.m_ibo);
		m_renderData.m_resources.push_back(m_renderData.m_ibo);

		// vertex array
		glGenVertexArrays(1, &m_renderData.m_vao);
		glBindVertexArray(m_renderData.m_vao);

		// normal buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_renderData.m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_renderData.m_normals.size() * sizeof(float), m_renderData.m_normals.data(), GL_STATIC_DRAW);

		// position buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_renderData.m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_renderData.m_vertexPositions.size() * sizeof(float), m_renderData.m_vertexPositions.data(), GL_STATIC_DRAW);

		// index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderData.m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_renderData.m_indices.size() * sizeof(uint32_t), m_renderData.m_indices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
}