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

	void Mesh::normalizeVertexData()
	{
		// sum for centroid
		float sumX{};
		float sumY{};
		float sumZ{};

		// find min and max vertex postition
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float minZ = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();
		float maxZ = std::numeric_limits<float>::min();
		for (int32_t i = 0; i < m_renderData.m_vertexPositions.size(); i += 3)
		{
			// min
			if (m_renderData.m_vertexPositions[i] < minX)
				minX = m_renderData.m_vertexPositions[i];
			if (m_renderData.m_vertexPositions[i + 1] < minY)
				minY = m_renderData.m_vertexPositions[i + 1];
			if (m_renderData.m_vertexPositions[i + 2] < minZ)
				minZ = m_renderData.m_vertexPositions[i + 2];

			// max
			if (m_renderData.m_vertexPositions[i] > maxX)
				maxX = m_renderData.m_vertexPositions[i];
			if (m_renderData.m_vertexPositions[i + 1] > maxY)
				maxY = m_renderData.m_vertexPositions[i + 1];
			if (m_renderData.m_vertexPositions[i + 2] > maxZ)
				maxZ = m_renderData.m_vertexPositions[i + 2];

			// add to sum
			sumX += m_renderData.m_vertexPositions[i];
			sumY += m_renderData.m_vertexPositions[i + 1];
			sumZ += m_renderData.m_vertexPositions[i + 2];
		}

		// calculate centroid
		std::size_t numVertices{ m_renderData.m_vertexPositions.size() / 3 };
		m_transformData.m_centroid = glm::vec3{ sumX / numVertices, sumY / numVertices, sumZ / numVertices };

		// calculate scale
		float rangeX = maxX - minX;
		float rangeY = maxY - minY;
		float rangeZ = maxZ - minZ;
		float scaleX = 2.0f / rangeX;
		float scaleY = 2.0f / rangeY;
		float scaleZ = 2.0f / rangeZ;

		// normalize
		for (int32_t i = 0; i < m_renderData.m_vertexPositions.size(); i += 3)
		{
			m_renderData.m_vertexPositions[i] = (m_renderData.m_vertexPositions[i] - minX) * scaleX;
			m_renderData.m_vertexPositions[i + 1] = (m_renderData.m_vertexPositions[i + 1] - minY) * scaleY;
			m_renderData.m_vertexPositions[i + 2] = (m_renderData.m_vertexPositions[i + 2] - minZ) * scaleZ;
		}
	}
}