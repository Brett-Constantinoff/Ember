#pragma once
#include "../core/Window.h"
#include "../core//Gui.h"
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
		void updateGui();
		void renderGui();
		
	private:
		const RendererCreateInfo m_createInfo;
		glm::mat4 m_perspective;
		glm::mat4 m_view;
		bool m_wireFrameEnabled;
	};
}