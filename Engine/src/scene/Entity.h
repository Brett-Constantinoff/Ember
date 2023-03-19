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
		SKYBOX,
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
	};
	
	struct EntityCreateInfo
	{
		EntityType m_type{ EntityType::NO_TYPE };
		std::string m_name{};
		std::string m_objFile{};
		std::string m_mtlFile{};

		glm::vec3 m_position{};
		glm::vec3 m_rotatoinAxis{0.0f};
		glm::vec3 m_scale{ 1.0f };
	};

	class Entity
	{
	public:
		Entity(const EntityCreateInfo& createInfo);
		~Entity();

		EntityType& getType();
		std::string getName();
		glm::vec3& getCentroid();
		glm::vec3& getPosition();
		glm::vec3& getScale();
		glm::vec3& getRotationAxis();
		std::vector<std::shared_ptr<Mesh>> getMeshes();
		bool& getWireFrame();
		

	private:
		void createMeshes();
		void calculateCentroid();
		void normalize(tinyobj::attrib_t& attrib);
		void createWithMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
			const tinyobj::attrib_t& attrib);
		void createWithoutMaterials(const std::vector<tinyobj::material_t>& materials, const std::vector<tinyobj::shape_t>& shapes,
			const tinyobj::attrib_t& attrib);
		void createSkyboxMesh(const tinyobj::attrib_t& attrib);

	private:
		EntityCreateInfo m_createInfo;
		tinyobj::attrib_t m_attrib;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		glm::vec3 m_centroid;
		bool m_wireFrame;
	};
}