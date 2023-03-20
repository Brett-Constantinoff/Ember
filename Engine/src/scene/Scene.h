#pragma once
#include "../renderer/Shader.h"
#include "../core/Memory.h"
#include "Camera.h"
#include "Entity.h"
#include <stdint.h>
#include <memory>
#include <filesystem>
#include <string>

namespace Ember::Scene
{
	// holds different shading effects
	enum class SceneShading
	{
		BASIC,
		CUSTOM,
	};

	struct SceneCreateInfo
	{
		std::shared_ptr<Camera> m_camera{};
		std::shared_ptr<Renderer::Shader> m_customShader{};
		SceneShading m_sceneShading{};
		bool m_enableSkybox{};
	};

	class Scene
	{
	public:

		struct EntityFileData
		{
			EntityFileData(const tinyobj::attrib_t& attrib, const std::vector<tinyobj::shape_t>& shapes,
				const std::vector<tinyobj::material_t>& materials) :
				m_attrib{ attrib }, m_shapes{ shapes }, m_materials{ materials }
			{

			}

			tinyobj::attrib_t m_attrib{};
			std::vector<tinyobj::shape_t> m_shapes{};
			std::vector<tinyobj::material_t> m_materials{};
		};

		Scene(const SceneCreateInfo& createInfo);
		~Scene();

		void addEntity(Entity* e);
		std::vector<std::shared_ptr<Entity>> getEntities() const;
		bool getSkyboxEnabled() const;
		int32_t getMeshCount() const;
		int32_t getVertexCount() const;
		int32_t getPolygonCount() const;
		int32_t getDifferingObjects() const;
		int32_t getEntityCount() const;
		std::shared_ptr<Camera> getCamera() const;
		std::shared_ptr<Renderer::Shader> getShader() const;
		std::shared_ptr<Renderer::Shader> getSkyboxShader() const;
		std::shared_ptr<Entity> getSkybox() const;

	private:
		void setupShaders();

	private:
		SceneCreateInfo m_createInfo;
		std::shared_ptr<Renderer::Shader> m_sceneShader;
		std::shared_ptr<Renderer::Shader> m_skyboxShader;
		std::vector<std::shared_ptr<Entity>> m_sceneEntities;
		std::shared_ptr<Entity> m_skyBox;
		std::unordered_map<std::string, EntityFileData> m_fileDataMap;
	};
}