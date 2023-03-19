#pragma once
#include "../renderer/Shader.h"
#include "../core/Memory.h"
#include "Camera.h"
#include "Entity.h"
#include <stdint.h>
#include <memory>

namespace Ember::Scene
{
	struct SceneCreateInfo
	{
		std::shared_ptr<Camera> m_camera{};
		std::shared_ptr<Renderer::Shader> m_shader{};
		std::shared_ptr<Renderer::Shader> m_skyboxShader{};
	};

	class Scene
	{
	public:
		Scene(const SceneCreateInfo& createInfo);
		~Scene();

		void addEntity(Entity* e);
		void addSkybox(Entity* skybox);
		std::vector<std::shared_ptr<Entity>> getEntities() const;
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
		SceneCreateInfo m_createInfo;
		std::vector<std::shared_ptr<Entity>> m_sceneEntities;
		std::shared_ptr<Entity> m_skyBox;
		std::unordered_map<std::string, tinyobj::attrib_t> m_attribMap;
	};
}