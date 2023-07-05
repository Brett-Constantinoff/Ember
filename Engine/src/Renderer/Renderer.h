#pragma once
#include "../core/ImageLoading.h"
#include "../core/Window.h"
#include "../core//Gui.h"
#include "../Core/Logger.h"
#include "../scene/Scene.h"
#include "../scene/Entity.h"

#include <string>
#include <memory>

namespace Ember::Renderer
{
	// more will be added in the future
	struct RendererCreateInfo
	{
		std::string m_api{};
		glm::vec4 m_backgroundCol{};
		std::shared_ptr<Core::Window> m_window{};
		std::shared_ptr<Scene::Scene> m_scene{};
		bool m_guiEnabled{};
		std::shared_ptr<Core::Gui> m_gui{};
	};

	class Renderer
	{
	public:
		Renderer(const RendererCreateInfo& createInfo);
		~Renderer();

		void update(float dt);
		void render();

	private:
		void loadSkybox();
		void updateGui();
		void renderGui();
		void renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh);
		void renderSkybox();
		
	private:
		const RendererCreateInfo m_createInfo;
		glm::mat4 m_perspective;
		glm::mat4 m_view;
	};
}