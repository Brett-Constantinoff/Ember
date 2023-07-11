#pragma once
#include <string.h>

#include "Window.h"

namespace Ember::Core
{
	// for now this is all this need, may add more in the future
	struct ApplicationCreateInfo
	{
		std::string m_label{};
	};

	class Application
	{
	public:
		Application(const ApplicationCreateInfo& createInfo);
		~Application();

		virtual void run() {};

	private:
		virtual void onStart() {};
		virtual void onUpdate(float dt) {};
		virtual void onRender() {};

	private:
		const ApplicationCreateInfo m_createInfo;
	};
}
