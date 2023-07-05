#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_backend{ nullptr }
	{
		if (m_createInfo.m_api == RendererApi::Opengl)
			m_backend = std::make_unique<OpenglBackend>();
		if (m_createInfo.m_api == RendererApi::Vulkan)
			m_backend = std::make_unique<VulkanBackend>();

		m_backend->init(m_createInfo);
	}

	Renderer::~Renderer()
	{
		m_backend->destroy();
	}

	void Renderer::update(float dt)
	{
		m_backend->update(dt);
	}
	
	void Renderer::render()
	{
		m_backend->render();
	}
}