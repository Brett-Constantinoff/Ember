#pragma once
#include "..//core/OpenGL.h"
#include "../core/TinyObj.h"
#include "../core/Glm.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <filesystem>
#include <fstream>

namespace Ember::Scene
{
	enum class EntityType
	{
		NO_TYPE,
		RENDERABLE,
		DIRECTIONAL_LIGHT,
		POINT_LIGHT
	};
	

	struct EntityCreateInfo
	{
		EntityType m_type{ EntityType::NO_TYPE };
		std::string m_name{};
		std::string m_objFile{};
		std::string m_mtlFile{};
	};

	class Entity
	{
	public:
		Entity(const EntityCreateInfo& createInfo);
		~Entity();

		EntityType& getType();
		glm::vec3& getCentroid();
		std::vector<std::shared_ptr<Mesh>> getMeshes();

		void rotate(float angle, const glm::vec3& axis);

	private:
		void createMeshes();
		void normalize(tinyobj::attrib_t& attrib);
		void createWithMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
			const tinyobj::attrib_t& attrib);
		void createWithoutMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
			const tinyobj::attrib_t& attrib);

	private:
		EntityCreateInfo m_createInfo;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		glm::vec3 m_centroid;
	};
}