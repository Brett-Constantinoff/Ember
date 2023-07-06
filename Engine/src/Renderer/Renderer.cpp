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
		{
			m_currentBackend = m_openglBackend;
			Core::Logger::getInstance().logInfo(std::string{"Using OpenGL specification"}, __FILE__);
		}
		else
		{
			m_currentBackend = m_vulkanBackend;
			Core::Logger::getInstance().logInfo(std::string{"Using Vulkan specification"}, __FILE__);
		}

		m_currentBackend->init(m_createInfo);
	}

	Renderer::~Renderer()
	{
		m_currentBackend->destroy();
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