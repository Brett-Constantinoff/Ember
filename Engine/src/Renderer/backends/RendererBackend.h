#pragma once
#include <memory>

#include "../../scene/Entity.h"
#include "../../core/Window.h"
#include "../../core//Gui.h"
#include "../../scene/Scene.h"
#include "../../scene/Entity.h"

namespace Ember::Renderer
{
	// more will be added in the future
	struct RendererCreateInfo
	{
		glm::vec4 m_backgroundCol{};
		std::shared_ptr<Core::Window> m_window{};
		std::shared_ptr<Scene::Scene> m_scene{};
		bool m_guiEnabled{};
		std::shared_ptr<Core::Gui> m_gui{};
	};


	 // nothing should access a backend except for the renderer
	class RendererBackend
	{
	protected:
		virtual void init(const RendererCreateInfo& createInfo) {};
		virtual void destroy() {};
		virtual void update(float dt) {};
		virtual void render() {};
		virtual void loadSkybox() {};
		void updateGui()
		{
			if (m_createInfo.m_guiEnabled)
				m_createInfo.m_gui->update();
		}

		void renderGui()
		{
			if (m_createInfo.m_guiEnabled)
				m_createInfo.m_gui->render();
		}
		virtual void renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh) {};
		virtual void renderSkybox() {};

		virtual void initMeshRenderData(const std::shared_ptr<Scene::Mesh>& mesh) {};
		virtual void initMeshTextures(const std::shared_ptr < Scene::Mesh>& mesh) {};
		virtual void loadMeshTexture(const std::string& texture) {};
		virtual void setupShaders() {};

	protected:
		RendererCreateInfo m_createInfo{};
		glm::mat4 m_perspective{};
		glm::mat4 m_view{};
		friend class Renderer;
	};
}