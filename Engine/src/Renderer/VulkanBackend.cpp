#include "VulkanBackend.h"

namespace Ember::Renderer
{
	void VulkanBackend::init(const RendererCreateInfo& createInfo)
	{
		m_createInfo = createInfo;
		createInstance();
	}

	void VulkanBackend::destroy()
	{
		vkDestroyInstance(m_instance, nullptr);
	}

	void VulkanBackend::update(float dt)
	{
		updateGui();

		// update the projection matrix
		float aspect = static_cast<float>(m_createInfo.m_window->getWidth()) / static_cast<float>(m_createInfo.m_window->getHeight());
		float near = m_createInfo.m_scene->getCamera()->getNear();
		float far = m_createInfo.m_scene->getCamera()->getFar();
		float zoom = m_createInfo.m_scene->getCamera()->getZoom();
		m_perspective = glm::perspective(glm::radians(zoom), aspect, near, far);

		// update view
		m_view = m_createInfo.m_scene->getCamera()->getView();

		m_createInfo.m_scene->getCamera()->move(dt);
	}

	void VulkanBackend::render()
	{
		
	}

	void VulkanBackend::loadSkybox()
	{

	}

	void VulkanBackend::renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh)
	{
		
	}

	void VulkanBackend::renderSkybox()
	{

	}

	void VulkanBackend::createInstance()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Ember";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Ember";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_3;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		Core::WindowExtensions extensions{m_createInfo.m_window->getExtensions()};
		createInfo.enabledExtensionCount = extensions.m_count;
		createInfo.ppEnabledExtensionNames = extensions.m_extensions;

		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{"Failed to create vulkan instance"}, __FILE__);
		else
			Core::Logger::getInstance().logInfo(std::string{"Successfully created vulkan instance"}, __FILE__);
	}
}