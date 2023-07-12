#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_currentBackend{ nullptr },
		m_openglBackend{nullptr}, m_vulkanBackend{nullptr}
	{
		//m_openglBackend = std::make_shared<OpenglBackend>();
		//m_openglBackend->init(m_createInfo);
		m_vulkanBackend = std::make_shared<VulkanBackend>();
		m_vulkanBackend->init(m_createInfo);

		if (m_createInfo.m_window->getApi() == Core::WindowApi::OpenGL)
			m_currentBackend = m_openglBackend;
		else
			m_currentBackend = m_vulkanBackend;

		Core::Logger::getInstance().logInfo(std::string{"Renderer created"}, __FILE__);
	}

	Renderer::~Renderer()
	{
		//m_openglBackend->destroy();
		m_vulkanBackend->destroy();

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