#include "Entity.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>

namespace Ember::Scene
{
	Entity::Entity(const EntityCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_meshes{}, m_centroid{}, m_wireFrame{false}
	{
	}

	Entity::~Entity()
	{
	}

	EntityType Entity::getType() const
	{
		return m_createInfo.m_type;
	}

	std::string Entity::getName() const
	{
		return m_createInfo.m_name;
	}

	glm::vec3& Entity::getCentroid()
	{
		return m_centroid;
	}

	glm::vec3& Entity::getPosition()
	{
		return m_createInfo.m_position;
	}

	glm::vec3& Entity::getScale()
	{
		return m_createInfo.m_scale;
	}

	glm::vec3& Entity::getRotationAxis()
	{
		return m_createInfo.m_rotatoinAxis;
	}
	
	bool& Entity::getWireFrame()
	{
		return m_wireFrame;
	}

	std::vector<std::shared_ptr<Mesh>> Entity::getMeshes() const
	{
		return m_meshes;
	}

	void Entity::normalize()
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
		for (int32_t i = 0; i < m_attrib.vertices.size(); i += 3)
		{
			// min
			if (m_attrib.vertices[i] < minX)
				minX = m_attrib.vertices[i];
			if (m_attrib.vertices[i + 1] < minY)
				minY = m_attrib.vertices[i + 1];
			if (m_attrib.vertices[i + 2] < minZ)
				minZ = m_attrib.vertices[i + 2];

			// max
			if (m_attrib.vertices[i] > maxX)
				maxX = m_attrib.vertices[i];
			if (m_attrib.vertices[i + 1] > maxY)
				maxY = m_attrib.vertices[i + 1];
			if (m_attrib.vertices[i + 2] > maxZ)
				maxZ = m_attrib.vertices[i + 2];

			// add to sum
			sumX += m_attrib.vertices[i];
			sumY += m_attrib.vertices[i + 1];
			sumZ += m_attrib.vertices[i + 2];
		}

		// calculate centroid
		std::size_t numVertices{ m_attrib.vertices.size() / 3 };

		// calculate scale
		float rangeX = maxX - minX;
		float rangeY = maxY - minY;
		float rangeZ = maxZ - minZ;
		float scaleX = 2.0f / rangeX;
		float scaleY = 2.0f / rangeY;
		float scaleZ = 2.0f / rangeZ;

		// normalize
		for (int32_t i = 0; i < m_attrib.vertices.size(); i += 3)
		{
			m_attrib.vertices[i] = (m_attrib.vertices[i] - minX) * scaleX;
			m_attrib.vertices[i + 1] = (m_attrib.vertices[i + 1] - minY) * scaleY;
			m_attrib.vertices[i + 2] = (m_attrib.vertices[i + 2] - minZ) * scaleZ;
		}
	}

	void Entity::createMeshes(bool loadObj)
	{
		// load the obj data only if neccessary
		if (loadObj)
		{
			std::string err{};
			std::string warn{};

			bool result{ tinyobj::LoadObj(&m_attrib, &m_shapes, &m_materials, &warn, &err, m_createInfo.m_objFile.c_str(), m_createInfo.m_mtlFile.c_str()) };
			if (!err.empty())
				throw std::runtime_error{ "OBJ ERROR {" + m_createInfo.m_objFile +  "} :: " + err};
		}

		// normalize the data first
		if (m_createInfo.m_type == EntityType::RENDERABLE)
		{
			normalize();
			calculateCentroid();

			// if the obj file has materials, we create a separate mesh per material
			if (m_materials.size() > 0)
				createWithMaterials();

			// otherwise we just create one mesh with default material colors
			else
				createWithoutMaterials();
		}
			
		// create skybox
		if (m_createInfo.m_type == EntityType::SKYBOX)
			createSkyboxMesh();
	}

	void Entity::calculateCentroid()
	{

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
		for (int32_t i = 0; i < m_attrib.vertices.size(); i += 3)
		{
			// min
			if (m_attrib.vertices[i] < minX)
				minX = m_attrib.vertices[i];
			if (m_attrib.vertices[i + 1] < minY)
				minY = m_attrib.vertices[i + 1];
			if (m_attrib.vertices[i + 2] < minZ)
				minZ = m_attrib.vertices[i + 2];

			// max
			if (m_attrib.vertices[i] > maxX)
				maxX = m_attrib.vertices[i];
			if (m_attrib.vertices[i + 1] > maxY)
				maxY = m_attrib.vertices[i + 1];
			if (m_attrib.vertices[i + 2] > maxZ)
				maxZ = m_attrib.vertices[i + 2];

			// add to sum
			sumX += m_attrib.vertices[i];
			sumY += m_attrib.vertices[i + 1];
			sumZ += m_attrib.vertices[i + 2];
		}

		// calculate centroid
		std::size_t numVertices{m_attrib.vertices.size() / 3 };
		m_centroid = glm::vec3{ sumX / numVertices, sumY / numVertices, sumZ / numVertices };
	}

	void Entity::createWithMaterials()
	{
		// loop over each material
		for (std::size_t i{ 0 }; i < m_materials.size(); i++)
		{
			RenderData renderData{};

			// set material data
			Material material{};
			material.m_ambient = { m_materials[i].ambient[0], m_materials[i].ambient[1] , m_materials[i].ambient[2] };
			material.m_diffuse = { m_materials[i].diffuse[0], m_materials[i].diffuse[1] , m_materials[i].diffuse[2] };
			material.m_specular = { m_materials[i].specular[0], m_materials[i].specular[1] , m_materials[i].specular[2] };
			material.m_texturePath = m_createInfo.m_mtlFile;
			material.m_diffuseTexture = m_materials[i].diffuse_texname;
			renderData.m_material = material;

			// loop over each shape
			for (const auto& shape : m_shapes)
			{
				std::size_t startIndex{ 0 };
				for (std::size_t j{ 0 }; j < shape.mesh.num_face_vertices.size(); j++)
				{
					if (shape.mesh.material_ids[j] == i)
					{
						// process indices for this face
						std::size_t numFaceVertices{ shape.mesh.num_face_vertices[j] };
						for (std::size_t k{ 0 }; k < numFaceVertices; k++)
						{
							auto index{ shape.mesh.indices[startIndex + k].vertex_index };
							renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3]);
							renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3 + 1]);
							renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3 + 2]);

							index = shape.mesh.indices[startIndex + k].normal_index;
							if (index >= 0)
							{
								renderData.m_normals.push_back(m_attrib.normals[index * 3]);
								renderData.m_normals.push_back(m_attrib.normals[index * 3 + 1]);
								renderData.m_normals.push_back(m_attrib.normals[index * 3 + 2]);
							}

							index = shape.mesh.indices[startIndex + k].texcoord_index;
							if (index >= 0)
							{
								renderData.m_uvCoords.push_back(m_attrib.texcoords[index * 2]);
								renderData.m_uvCoords.push_back(m_attrib.texcoords[index * 2 + 1]);
							}
						}

						startIndex += numFaceVertices;
					}
					else
					{
						startIndex += shape.mesh.num_face_vertices[j];
					}
				}
			}
			m_meshes.emplace_back(new Mesh(renderData));
		}
	}

	void Entity::createWithoutMaterials()
	{
		RenderData renderData{};

		// set material data
		Material material{};
		material.m_ambient = { 0.0, 0.0 , 0.0 };
		material.m_diffuse = { 0.5f, 0.5f, 0.5f};
		renderData.m_material = material;

		// loop over each shape
		for (const auto& shape : m_shapes)
		{
			std::size_t startIndex{ 0 };
			for (std::size_t j{ 0 }; j < shape.mesh.num_face_vertices.size(); j++)
			{
				// process indices for this face
				std::size_t numFaceVertices{ shape.mesh.num_face_vertices[j] };
				for (std::size_t k{ 0 }; k < numFaceVertices; k++)
				{
					auto index{ shape.mesh.indices[startIndex + k].vertex_index };
					renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3]);
					renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3 + 1]);
					renderData.m_vertexPositions.push_back(m_attrib.vertices[index * 3 + 2]);

					index = shape.mesh.indices[startIndex + k].normal_index;
					if (index >= 0)
					{
						renderData.m_normals.push_back(m_attrib.normals[index * 3]);
						renderData.m_normals.push_back(m_attrib.normals[index * 3 + 1]);
						renderData.m_normals.push_back(m_attrib.normals[index * 3 + 2]);
					}
				}
				startIndex += numFaceVertices;
			}
		}
		m_meshes.emplace_back(new Mesh(renderData));
	}

	void Entity::createSkyboxMesh()
	{
		// nothing special just copy over vertex positions
		RenderData renderData{};
		Material material{};
		renderData.m_vertexPositions = m_attrib.vertices;
		m_meshes.emplace_back(new Mesh(renderData));
	}
}