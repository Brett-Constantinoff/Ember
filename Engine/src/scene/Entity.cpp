#include "Entity.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>

namespace Ember::Scene
{
	Entity::Entity(const EntityCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_meshes{}, m_centroid{}
	{
		createMeshes();
	}

	Entity::~Entity()
	{
	}

	EntityType& Entity::getType()
	{
		return m_createInfo.m_type;
	}

	std::vector<std::shared_ptr<Mesh>> Entity::getMeshes()
	{
		return m_meshes;
	}

	void Entity::normalize(tinyobj::attrib_t& attrib)
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
		for (int32_t i = 0; i < attrib.vertices.size(); i += 3)
		{
			// min
			if (attrib.vertices[i] < minX)
				minX = attrib.vertices[i];
			if (attrib.vertices[i + 1] < minY)
				minY = attrib.vertices[i + 1];
			if (attrib.vertices[i + 2] < minZ)
				minZ = attrib.vertices[i + 2];

			// max
			if (attrib.vertices[i] > maxX)
				maxX = attrib.vertices[i];
			if (attrib.vertices[i + 1] > maxY)
				maxY = attrib.vertices[i + 1];
			if (attrib.vertices[i + 2] > maxZ)
				maxZ = attrib.vertices[i + 2];

			// add to sum
			sumX += attrib.vertices[i];
			sumY += attrib.vertices[i + 1];
			sumZ += attrib.vertices[i + 2];
		}

		// calculate centroid
		std::size_t numVertices{ attrib.vertices.size() / 3 };
		m_centroid = glm::vec3{ sumX / numVertices, sumY / numVertices, sumZ / numVertices };

		// calculate scale
		float rangeX = maxX - minX;
		float rangeY = maxY - minY;
		float rangeZ = maxZ - minZ;
		float scaleX = 2.0f / rangeX;
		float scaleY = 2.0f / rangeY;
		float scaleZ = 2.0f / rangeZ;

		// normalize
		for (int32_t i = 0; i < attrib.vertices.size(); i += 3)
		{
			attrib.vertices[i] = (attrib.vertices[i] - minX) * scaleX;
			attrib.vertices[i + 1] = (attrib.vertices[i + 1] - minY) * scaleY;
			attrib.vertices[i + 2] = (attrib.vertices[i + 2] - minZ) * scaleZ;
		}
	}

	void Entity::createMeshes()
	{
		// parse obj file
		tinyobj::attrib_t attrib{};
		std::vector<tinyobj::shape_t> shapes{};
		std::vector<tinyobj::material_t> materials{};
		std::string err{};
		std::string warn{};
		
		bool result{ tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, m_createInfo.m_objFile.c_str(), m_createInfo.m_mtlFile.c_str()) };
		if (!err.empty())
			throw std::runtime_error{ "OBJ ERROR {" + m_createInfo.m_mtlFile + "} :: " + err };

		// normalize the data first
		normalize(attrib);

		// if the obj file has materials, we create a separate mesh per material
		if (materials.size() > 0)
			createWithMaterials(materials, shapes, attrib);

		// otherwise we just create one mesh with default material colors
		else
			createWithoutMaterials(materials, shapes, attrib);

	}

	void Entity::createWithMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
		const tinyobj::attrib_t& attrib)
	{
		// loop over each material
		for (std::size_t i{ 0 }; i < materials.size(); i++)
		{
			RenderData renderData{};

			// set material data
			Material material{};
			material.m_ambient = { materials[i].ambient[0], materials[i].ambient[1] , materials[i].ambient[2] };
			material.m_diffuse = { materials[i].diffuse[0], materials[i].diffuse[1] , materials[i].diffuse[2] };
			renderData.m_material = material;

			// loop over each shape
			for (const auto& shape : shapes)
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
							renderData.m_vertexPositions.push_back(attrib.vertices[index * 3]);
							renderData.m_vertexPositions.push_back(attrib.vertices[index * 3 + 1]);
							renderData.m_vertexPositions.push_back(attrib.vertices[index * 3 + 2]);

							index = shape.mesh.indices[startIndex + k].normal_index;
							if (index >= 0)
							{
								renderData.m_normals.push_back(attrib.normals[index * 3]);
								renderData.m_normals.push_back(attrib.normals[index * 3 + 1]);
								renderData.m_normals.push_back(attrib.normals[index * 3 + 2]);
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

	void Entity::createWithoutMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
		const tinyobj::attrib_t& attrib)
	{
		RenderData renderData{};

		// set material data
		Material material{};
		material.m_ambient = { 0.0, 0.0 , 0.0 };
		material.m_diffuse = { 0.5f, 0.5f, 0.5f};
		renderData.m_material = material;

		// loop over each shape
		for (const auto& shape : shapes)
		{
			std::size_t startIndex{ 0 };
			for (std::size_t j{ 0 }; j < shape.mesh.num_face_vertices.size(); j++)
			{
				// process indices for this face
				std::size_t numFaceVertices{ shape.mesh.num_face_vertices[j] };
				for (std::size_t k{ 0 }; k < numFaceVertices; k++)
				{
					auto index{ shape.mesh.indices[startIndex + k].vertex_index };
					renderData.m_vertexPositions.push_back(attrib.vertices[index * 3]);
					renderData.m_vertexPositions.push_back(attrib.vertices[index * 3 + 1]);
					renderData.m_vertexPositions.push_back(attrib.vertices[index * 3 + 2]);

					index = shape.mesh.indices[startIndex + k].normal_index;
					if (index >= 0)
					{
						renderData.m_normals.push_back(attrib.normals[index * 3]);
						renderData.m_normals.push_back(attrib.normals[index * 3 + 1]);
						renderData.m_normals.push_back(attrib.normals[index * 3 + 2]);
					}
				}
				startIndex += numFaceVertices;
			}
		}
		m_meshes.emplace_back(new Mesh(renderData));
	}
}