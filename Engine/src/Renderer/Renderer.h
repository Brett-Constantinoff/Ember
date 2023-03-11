#pragma once
#include "../core/Window.h"
#include "../core/ImGui.h"
#include "../scene/Scene.h"

#include <string>
#include <memory>

namespace Ember::Renderer
{
	// more will be added in the future
	struct RendererCreateInfo
	{
		std::string m_api{};
		Ember::Core::Window* m_window{};
		Ember::Scene::Scene* m_scene{};
		bool m_imguiEnabled{};
	};

	class Renderer
	{
	public:
		Renderer(const RendererCreateInfo& createInfo);
		~Renderer();

		void update(float dt);
		void render();
		
	private:
		void initImgui();
		void updateImgui();
		void renderImgui();

	private:
		const RendererCreateInfo m_createInfo;

	};
}