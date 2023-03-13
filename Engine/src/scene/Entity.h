#pragma once
#include "..//core/OpenGL.h"
#include "../core/TinyObj.h"
#include "../core/Glm.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

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
		std::vector<std::string> m_diffuseTextures{};
		std::vector<std::string> m_normalTextures{};
	};

	class Entity
	{
	public:
		Entity(const EntityCreateInfo& createInfo);
		~Entity();

		EntityType& getType();
		Mesh& getMesh();
		void rotateFixedY(float angle);

	private:
		EntityCreateInfo m_createInfo;
		Mesh m_mesh;
	};
}