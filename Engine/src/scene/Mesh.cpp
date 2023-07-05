#include "Mesh.h"
#include <iostream>

namespace Ember::Scene
{
	Mesh::Mesh(const RenderData& renderData) :
		 m_renderData{renderData}
	{
		initRenderData();
		initTextures();
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

		// text coords
		if (m_renderData.m_uvCoords.size() != 0)
		{
			glGenBuffers(1, &m_renderData.m_uvbo);
			m_renderData.m_resources.push_back(m_renderData.m_uvbo);

			// uv buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_renderData.m_uvbo);
			glBufferData(GL_ARRAY_BUFFER, m_renderData.m_uvCoords.size() * sizeof(float), m_renderData.m_uvCoords.data(), GL_STATIC_DRAW);

			// uv attribute attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(2);
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

	void Mesh::initTextures()
	{
		if (!m_renderData.m_material.m_diffuseTexture.empty())
		{
			glGenTextures(1, &m_renderData.m_diffuseTexId);
			glBindTexture(GL_TEXTURE_2D, m_renderData.m_diffuseTexId);
			loadTexture(m_renderData.m_material.m_texturePath + m_renderData.m_material.m_diffuseTexture);
			m_renderData.m_textures.push_back(m_renderData.m_diffuseTexId);
		}
	}

	void Mesh::loadTexture(const std::string& texture)
	{
		int32_t width{};
		int32_t height{};
		int32_t channels{};

		stbi_set_flip_vertically_on_load_thread(true);
		uint8_t* data = stbi_load(texture.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			GLenum format{};
			if (channels == 1)
				format = GL_RED;
			else if (channels == 3)
				format = GL_RGB;
			else if (channels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else
		{
			Core::Logger::getInstance().logError(std::string{"ERROR LOADING TEXTURE: " + texture}, __FILE__);
		}
	}
}