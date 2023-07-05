#pragma once
#include "OpenglBackend.h"
#include "VulkanBackend.h"
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
		std::unique_ptr<RendererBackend> m_backend;
	};
}