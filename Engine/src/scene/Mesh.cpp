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
		for (const auto& resource : m_renderData.m_textures)
			glDeleteTextures(1, &resource);

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
		// vertex array
		glGenVertexArrays(1, &m_renderData.m_vao);
		glBindVertexArray(m_renderData.m_vao);

		// normals
		if (m_renderData.m_normals.size() != 0)
		{
			glGenBuffers(1, &m_renderData.m_nbo);
			m_renderData.m_resources.push_back(m_renderData.m_nbo);

			// normal buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_renderData.m_nbo);
			glBufferData(GL_ARRAY_BUFFER, m_renderData.m_normals.size() * sizeof(float), m_renderData.m_normals.data(), GL_STATIC_DRAW);

			// normal attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
		}
		
		// positions
		glGenBuffers(1, &m_renderData.m_vbo);
		m_renderData.m_resources.push_back(m_renderData.m_vbo);
	
		// position buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_renderData.m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_renderData.m_vertexPositions.size() * sizeof(float), m_renderData.m_vertexPositions.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
}