#pragma once
#include "Window.h"
#include "../scene/Scene.h"

namespace Ember::Core
{
	struct GuiCreateInfo
	{
		Window* m_window;
		Ember::Scene::Scene* m_scene;
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