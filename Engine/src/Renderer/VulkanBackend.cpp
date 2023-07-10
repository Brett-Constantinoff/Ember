#include "VulkanBackend.h"

namespace Ember::Renderer
{
	struct VulkanBackend::QueueFamilyIndices
	{
	public:
		bool isComplete()
		{
			return m_graphicsFamily.has_value();
		}

	public:
		std::optional<uint32_t> m_graphicsFamily{};
	};

	void VulkanBackend::init(const RendererCreateInfo& createInfo)
	{
		m_createInfo = createInfo;
		m_indices = std::make_shared<QueueFamilyIndices>();

		createInstance();
		createPhysicalDevice();
	}

	void VulkanBackend::destroy()
	{
		vkDestroyDevice(m_logicalDevice, nullptr);
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

	void VulkanBackend::createPhysicalDevice()
	{
		uint32_t count{ 0 };
		vkEnumeratePhysicalDevices(m_instance, &count, nullptr);

		if (count == 0)
			Core::Logger::getInstance().logError(std::string{"No GPU's support Vulkan!"}, __FILE__);

		std::vector<VkPhysicalDevice> devices{};
		devices.resize(count);
		vkEnumeratePhysicalDevices(m_instance, &count, devices.data());

		for (const auto& device : devices)
		{
			if (physicalDeviceSuitable(device))
			{
				m_physicalDevice = device;
				break;
			}
		}

		if (m_physicalDevice == VK_NULL_HANDLE)
			Core::Logger::getInstance().logError(std::string{"Failed to find suitable GPU for Vulkan"}, __FILE__);

		Core::Logger::getInstance().logInfo(std::string{"Vulkan physical device created successfully"}, __FILE__);
	}

	void VulkanBackend::createLogicalDevice()
	{
		getQueueFamilies(m_physicalDevice);

		VkDeviceQueueCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		createInfo.queueFamilyIndex = m_indices->m_graphicsFamily.value();
		createInfo.queueCount = 1;

		float queuePriority{ 1.0f };
		createInfo.pQueuePriorities = &queuePriority;

		// TODO - Define some features for the future, right now its not important
		VkPhysicalDeviceFeatures features{};
		VkDeviceCreateInfo ci{};
		ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		ci.pQueueCreateInfos = &createInfo;
		ci.queueCreateInfoCount = 1;
		ci.pEnabledFeatures = &features;

		// TODO - Give layer count once implemented
		ci.enabledLayerCount = 0;

		if (vkCreateDevice(m_physicalDevice, &ci, nullptr, &m_logicalDevice) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{ "Failed to create Vulkan logical device" }, __FILE__);
		
		vkGetDeviceQueue(m_logicalDevice, m_indices->m_graphicsFamily.value(), 0, &m_graphicsQueue);
	}

	bool VulkanBackend::physicalDeviceSuitable(VkPhysicalDevice device)
	{
		// returns any gpu that supports vulkan
		// TODO: Add some other checks here ex. pick dedicated gpu instead of integrated graphics
		getQueueFamilies(device);
		return m_indices->isComplete();
	}

	void VulkanBackend::getQueueFamilies(VkPhysicalDevice device)
	{
		uint32_t count{ 0 };
		vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies{};
		queueFamilies.resize(count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queueFamilies.data());

		for (int32_t i{ 0 }; i < count; i++)
		{
			const auto& family{ queueFamilies[i] };
			if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				m_indices->m_graphicsFamily = i;
			if (m_indices->isComplete())
				break;
		}
	}
}