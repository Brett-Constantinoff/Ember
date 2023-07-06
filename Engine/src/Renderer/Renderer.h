#pragma once
#include "OpenglBackend.h"
#include "VulkanBackend.h"
#include "../Core/Logger.h"
#include <string>
#include <memory>

namespace Ember::Renderer
{
	class Renderer
	{
	public:
		Renderer(const RendererCreateInfo& createInfo);
		~Renderer();

		void update(float dt);
		void render();
		
	private:
		const RendererCreateInfo m_createInfo;
		std::shared_ptr<OpenglBackend> m_openglBackend;
		std::shared_ptr < VulkanBackend> m_vulkanBackend;
		std::shared_ptr<RendererBackend> m_currentBackend;
	};
}