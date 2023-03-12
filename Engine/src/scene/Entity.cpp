#include "Entity.h"

namespace Ember::Scene
{
	Entity::Entity(const EntityCreateInfo& createInfo) :
		m_createInfo{ createInfo }
	{
		// if we want to see the object on the screen
		if (m_createInfo.m_type == EntityType::RENDERABLE)
		{
			getVertexData();
			initRenderData();
		}
	}

	Entity::~Entity()
	{
		for (const auto& resource : m_renderData.resources)
			glDeleteBuffers(1, &resource);
		glDeleteVertexArrays(1, &m_renderData.m_vao);
	}

	EntityType Entity::getType() const
	{
		return m_createInfo.m_type;
	}

	RenderData& Entity::getRenderData()
	{
		return m_renderData;
	}

	void Entity::getVertexData()
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn{};
		std::string err{};
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, m_createInfo.m_objFile.c_str(), NULL, true);
		if (!err.empty() || !ret)
			throw std::runtime_error{ "ERROR::CANNOT PARSE OBJ FILE " + m_createInfo.m_objFile + ":" + err };

		// get vertex data
		m_renderData.m_vertexPositions = attrib.vertices;

		// get normals
		m_renderData.m_normals = attrib.normals;

		// get indices
		for (const auto& s : shapes)
		{
			for (std::size_t f = 0; f < s.mesh.indices.size() / 3; f++)
			{
				m_renderData.m_indices.push_back(s.mesh.indices[3 * f + 0].vertex_index);
				m_renderData.m_indices.push_back(s.mesh.indices[3 * f + 1].vertex_index);
				m_renderData.m_indices.push_back(s.mesh.indices[3 * f + 2].vertex_index);
			}
		}

		// normalize data into 0 - 1 range
		normalizeVertexData();
	}

	void Entity::normalizeVertexData()
	{
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
		}

		// normalize
		for (int32_t i = 0; i < m_renderData.m_vertexPositions.size(); i += 3)
		{
			m_renderData.m_vertexPositions[i] = (m_renderData.m_vertexPositions[i] - minX) / (maxX - minX);
			m_renderData.m_vertexPositions[i + 1] = (m_renderData.m_vertexPositions[i + 1] - minY) / (maxY - minY);
			m_renderData.m_vertexPositions[i + 2] = (m_renderData.m_vertexPositions[i + 2] - minZ) / (maxZ - minZ);
		}
	}

	void Entity::initRenderData()
	{
		// positions
		glGenBuffers(1, &m_renderData.m_vbo);
		m_renderData.resources.push_back(m_renderData.m_vbo);

		// normals
		glGenBuffers(1, &m_renderData.m_nbo);
		m_renderData.resources.push_back(m_renderData.m_nbo);

		// indices
		glGenBuffers(1, &m_renderData.m_ibo);
		m_renderData.resources.push_back(m_renderData.m_ibo);

		// vertex array
		glGenVertexArrays(1, &m_renderData.m_vao);
		glBindVertexArray(m_renderData.m_vao);

		// normal buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderData.m_nbo);
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