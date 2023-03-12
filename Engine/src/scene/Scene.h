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
		Ember::Scene::Camera* m_camera{};
		Ember::Renderer::Shader* m_shader{};
		GLFWwindow* m_windowContext{};
	};

	class Scene
	{
	public:
		Scene(const SceneCreateInfo& createInfo);
		~Scene();

		void addEntity(Entity* e);
		std::vector<std::shared_ptr<Entity>> getEntities();
		int32_t getVertexCount();
		int32_t getPolygonCount();

		int32_t getEntityCount() const;
		Ember::Scene::Camera* getCamera() const;
		Ember::Renderer::Shader* getShader() const;

	private:
		SceneCreateInfo m_createInfo;
		std::vector<std::shared_ptr<Entity>> m_sceneEntities;
	};
}