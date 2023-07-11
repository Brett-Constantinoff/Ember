#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <filesystem>
#include <fstream>

#include "../core/Logger.h"
#include "Mesh.h"

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

		EntityType getType() const;
		std::string getName() const;
		glm::vec3& getCentroid();
		glm::vec3& getPosition();
		glm::vec3& getScale();
		glm::vec3& getRotationAxis();
		std::vector<std::shared_ptr<Mesh>> getMeshes() const;
		bool& getWireFrame();
		
	private:
		void createMeshes(bool loadObj);
		void calculateCentroid();
		void normalize();
		void createWithMaterials();
		void createWithoutMaterials();
		void createSkyboxMesh();

	private:
		EntityCreateInfo m_createInfo;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		glm::vec3 m_centroid;
		bool m_wireFrame;
		tinyobj::attrib_t m_attrib{};
		std::vector<tinyobj::material_t> m_materials{};
		std::vector<tinyobj::shape_t> m_shapes{};

		// allow the scene to access things about an entity
		friend class Scene;
	};
}