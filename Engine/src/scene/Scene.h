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
		std::vector<std::shared_ptr<Entity>> getEntities();
		int32_t getMeshCount();
		int32_t getVertexCount();
		int32_t getPolygonCount();

		int32_t getEntityCount() const;
		std::shared_ptr<Camera> getCamera() const;
		std::shared_ptr<Renderer::Shader> getShader() const;
		std::shared_ptr<Renderer::Shader> getSkyboxShader() const;
		std::shared_ptr<Entity> getSkybox() const;
		bool& getWireFrame();

	private:
		SceneCreateInfo m_createInfo;
		std::vector<std::shared_ptr<Entity>> m_sceneEntities;
		std::shared_ptr<Entity> m_skyBox;
		bool m_wireframe;
	};
}