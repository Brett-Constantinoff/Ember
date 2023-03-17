#pragma once
#include "Window.h"
#include "../scene/Scene.h"

namespace Ember::Core
{
	struct GuiCreateInfo
	{
		std::shared_ptr<Window> m_window;
		std::shared_ptr<Scene::Scene> m_scene;
	};

	class Gui
	{
	public:
		Gui(const GuiCreateInfo& createInfo);
		virtual ~Gui() {};

		virtual void update() {};
		virtual void render() {};

	private:
		virtual void init() {};

	protected:
		GuiCreateInfo m_createInfo;
	};
}