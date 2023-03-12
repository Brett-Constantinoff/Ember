#pragma once
#include "..//core/OpenGL.h"
#include "../core/TinyObj.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace Ember::Scene
{
	enum class EntityType
	{
		NO_TYPE,
		RENDERABLE,
		DIRECTIONAL_LIGHT,
		POINT_LIGHT
	};
	
	struct RenderData
	{
		std::vector<float> m_vertexPositions{};
		std::vector<uint32_t> m_indices{};
		std::vector<float> m_normals{};

		// this contatins things created by opengl
		std::vector<uint32_t> resources;

		uint32_t m_vbo{};
		uint32_t m_ibo{};
		uint32_t m_nbo{};
		uint32_t m_vao{};
	};

	struct EntityCreateInfo
	{
		EntityType m_type{ EntityType::NO_TYPE };
		std::string m_name{};
		std::string m_objFile{};
	};

	class Entity
	{
	public:
		Entity(const EntityCreateInfo& createInfo);
		~Entity();

		EntityType getType() const;
		RenderData& getRenderData();

	private:
		void getVertexData();
		void normalizeVertexData();
		void initRenderData();

	private:
		EntityCreateInfo m_createInfo;
		RenderData m_renderData;
	};
}