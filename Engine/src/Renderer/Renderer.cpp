#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_currentBackend{ nullptr },
		m_openglBackend{nullptr}, m_vulkanBackend{nullptr}
	{
		m_openglBackend = std::make_shared<OpenglBackend>();
		m_vulkanBackend = std::make_shared<VulkanBackend>();

		if (m_createInfo.m_api == RendererApi::Opengl)
			m_currentBackend = m_openglBackend;
		else
			m_currentBackend = m_vulkanBackend;

		m_currentBackend->init(m_createInfo);

		Core::Logger::getInstance().logInfo(std::string{"Renderer created"}, __FILE__);
	}

	Renderer::~Renderer()
	{
		// currently only the vulkan backend needs cleanup
		if (m_createInfo.m_api == RendererApi::Vulkan)
			m_currentBackend->destroy();

		Core::Logger::getInstance().logInfo(std::string{"Renderer destroyed"}, __FILE__);
	}

	void Renderer::update(float dt)
	{
		m_currentBackend->update(dt);
	}
	
	void Renderer::render()
	{
		m_currentBackend->render();
	}
}