#pragma once
#include "Layer.h"
#include "Window.h"
#include "../../libs/imgui/imgui.h"
#include "../../libs/imgui/imgui_impl_glfw.h"
#include "../../libs/imgui/imgui_impl_opengl3.h"

namespace Ember
{
	namespace Core
	{
		class ImguiLayer : public Layer
		{
		public:
			ImguiLayer(const char* name, Window* win);
			~ImguiLayer();

			virtual void onUpdate(float dt);
			virtual void onRender();
		};
	}
}
