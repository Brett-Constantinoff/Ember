#include "VulkanBackend.h"

namespace Ember::Renderer
{
	///////////////// VULKAN STRUCTS //////////////////////
	//////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	struct VulkanBackend::QueueFamilyIndices
	{
	public:
		bool isComplete()
		{
			return m_graphicsFamily.has_value() &&
				m_presentFamily.has_value();
		}

	public:
		std::optional<uint32_t> m_graphicsFamily{};
		std::optional<uint32_t> m_presentFamily{};
	};

	struct VulkanBackend::SwapChainSupportDetails
	{
	public:
		VkSurfaceCapabilitiesKHR m_cap{};
		std::vector<VkSurfaceFormatKHR> m_formats{};
		std::vector<VkPresentModeKHR> m_presentModes{};
	};

	void VulkanBackend::init(const RendererCreateInfo& createInfo)
	{
		m_createInfo = createInfo;
		m_indices = std::make_shared<QueueFamilyIndices>();
		m_swapChainDetails = std::make_shared<SwapChainSupportDetails>();

		createInstance();
		createDebugMessenger();
		createSurface();
		createPhysicalDevice();
		createLogicalDevice();
		createSwapChain();
	}

	void VulkanBackend::destroy()
	{
		for (const auto& imageView : m_swapChainImageViews)
			vkDestroyImageView(m_logicalDevice, imageView, nullptr);

		if (m_enableValidationLayers)
			destroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

		vkDestroySwapchainKHR(m_logicalDevice, m_swapChain, nullptr);
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		vkDestroyDevice(m_logicalDevice, nullptr);
		vkDestroyInstance(m_instance, nullptr);
	}

	void VulkanBackend::update(float dt)
	{
		updateGui();

		// update the projection matrix
		/*
		float aspect = static_cast<float>(m_createInfo.m_window->getWidth()) / static_cast<float>(m_createInfo.m_window->getHeight());
		float near = m_createInfo.m_scene->getCamera()->getNear();
		float far = m_createInfo.m_scene->getCamera()->getFar();
		float zoom = m_createInfo.m_scene->getCamera()->getZoom();
		m_perspective = glm::perspective(glm::radians(zoom), aspect, near, far);
		*/

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

	void VulkanBackend::initMeshRenderData(const std::shared_ptr<Scene::Mesh>& mesh)
	{

	}

	void VulkanBackend::initMeshTextures(const std::shared_ptr < Scene::Mesh>& mesh)
	{

	}

	void VulkanBackend::loadMeshTexture(const std::string& texture)
	{

	}

	///////////////// VULKAN CREATION ////////////////////
	//////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	void VulkanBackend::createInstance()
	{
		if (m_enableValidationLayers && !checkValidationLayerSupport())
			Core::Logger::getInstance().logError(std::string{"No validation layers available"}, __FILE__);

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

		auto extensions{ getRequiredExtenions() };
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (m_enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			createInfo.ppEnabledLayerNames = m_validationLayers.data();

			populateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}

		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{"Failed to create vulkan instance"}, __FILE__);
	}

	void VulkanBackend::createDebugMessenger()
	{
		if (!m_enableValidationLayers)
			return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		populateDebugMessengerCreateInfo(createInfo);

		if (createDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{"Failed to create vulkan debug messanger"}, __FILE__);
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
	}

	void VulkanBackend::createLogicalDevice()
	{
		getQueueFamilies(m_physicalDevice);

		std::vector<VkDeviceQueueCreateInfo> createInfos{};
		std::set<uint32_t> uniqueQueueFamilies{{m_indices->m_graphicsFamily.value(), m_indices->m_presentFamily.value()}};

		float priority{ 1.0f };
		for (uint32_t family : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			createInfo.queueFamilyIndex = family;
			createInfo.queueCount = 1;
			createInfo.pQueuePriorities = &priority;
			createInfos.push_back(createInfo);
		}

		// TODO - Define some features for the future, right now its not important
		VkPhysicalDeviceFeatures features{};
		VkDeviceCreateInfo ci{};
		ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		ci.pQueueCreateInfos = createInfos.data();
		ci.queueCreateInfoCount = static_cast<uint32_t>(createInfos.size());
		ci.pEnabledFeatures = &features;
		ci.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
		ci.ppEnabledExtensionNames = m_deviceExtensions.data();

		if (m_enableValidationLayers)
		{
			ci.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			ci.ppEnabledLayerNames = m_validationLayers.data();
		}
		else
		{
			ci.enabledLayerCount = 0;
		}


		if (vkCreateDevice(m_physicalDevice, &ci, nullptr, &m_logicalDevice) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{ "Failed to create Vulkan logical device" }, __FILE__);
		
		vkGetDeviceQueue(m_logicalDevice, m_indices->m_graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_logicalDevice, m_indices->m_presentFamily.value(), 0, &m_presentQueue);
	}

	void VulkanBackend::createSurface()
	{
		VkWin32SurfaceCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(*m_createInfo.m_window->getContext());
		createInfo.hinstance = GetModuleHandle(nullptr);

		if (vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &m_surface) != VK_SUCCESS)
			Core::Logger::getInstance().logError(std::string{"Failed to create vulkan surface"}, __FILE__);
	}

	void VulkanBackend::createSwapChain()
	{
		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat();
		VkPresentModeKHR presentMode = chooseSwapPresentMode();
		VkExtent2D extent = chooseSwapExtent();
		
		uint32_t imageCount{ m_swapChainDetails->m_cap.minImageCount + 1 };
		uint32_t maxImageCount{ m_swapChainDetails->m_cap.maxImageCount };
		if (maxImageCount > 0 && imageCount > maxImageCount)
			imageCount = maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		getQueueFamilies(m_physicalDevice);
		uint32_t indices[] = { m_indices->m_graphicsFamily.value(),m_indices->m_graphicsFamily.value() };
		if (m_indices->m_graphicsFamily != m_indices->m_graphicsFamily) 
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = indices;
		}
		else 
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = m_swapChainDetails->m_cap.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_logicalDevice, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) 
			Core::Logger::getInstance().logError(std::string{"Failed to create vulkan swap chain"}, __FILE__);

		vkGetSwapchainImagesKHR(m_logicalDevice, m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_logicalDevice, m_swapChain, &imageCount, m_swapChainImages.data());

		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
	}

	void VulkanBackend::createImageViews()
	{
		m_swapChainImageViews.resize(m_swapChainImages.size());

		for (std::size_t i{0}; i < m_swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo ci{};
			ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ci.image = m_swapChainImages[i];
			ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ci.format = m_swapChainImageFormat;
			ci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			ci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			ci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			ci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			ci.subresourceRange.baseMipLevel = 0;
			ci.subresourceRange.levelCount = 1;
			ci.subresourceRange.baseArrayLayer = 0;
			ci.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_logicalDevice, &ci, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
				Core::Logger::getInstance().logError(std::string{"Failed to create vulkan image views"}, __FILE__);
		}
	}

	///////////////// VULKAN DESTRUCTION //////////////////
	//////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	void VulkanBackend::destroyDebugUtilsMessengerEXT(VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) 
			func(instance, debugMessenger, pAllocator);
	}

	///////////////// VULKAN UTILITIES ///////////////////
	//////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	bool VulkanBackend::physicalDeviceSuitable(VkPhysicalDevice device)
	{
		// returns any gpu that supports vulkan
		// TODO: Add some other checks here ex. pick dedicated gpu instead of integrated graphics
		getQueueFamilies(device);
		bool extensionsSupported{ checkDeviceExtensionSupport(device) };
		bool swapChainAdequate{ false };

		if (extensionsSupported)
		{
			querySwapChainSupport(device);
			swapChainAdequate = !m_swapChainDetails->m_formats.empty() && !m_swapChainDetails->m_presentModes.empty();
		}

		return m_indices->isComplete() && extensionsSupported && swapChainAdequate;
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

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

			if (presentSupport) 
				m_indices->m_presentFamily = i;
			
			if (m_indices->isComplete())
				break;
		}
	}

	bool VulkanBackend::checkValidationLayerSupport()
	{
		uint32_t count{};
		vkEnumerateInstanceLayerProperties(&count, nullptr);

		std::vector<VkLayerProperties> layers{};
		layers.resize(count);
		vkEnumerateInstanceLayerProperties(&count, layers.data());

		const int32_t length{ 256 };
		for (const auto layerName : m_validationLayers)
		{
			bool found{ false };

			for (const auto& layerProps : layers)
			{
				if (strncmp(layerName, layerProps.layerName, length))
				{
					found = true;
					break;
				}
			}

			if (!found)
				return false;
		}
		return true;
	}

	std::vector<const char*> VulkanBackend::getRequiredExtenions()
	{
		Core::WindowExtensions e{m_createInfo.m_window->getExtensions()};

		std::vector<const char*> extensions(e.m_extensions, e.m_extensions + e.m_count);

		if (m_enableValidationLayers)
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensions;
	}

	bool VulkanBackend::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t count{};
		vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

		std::vector<VkExtensionProperties> extensions{};
		extensions.resize(count);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &count, extensions.data());
		std::vector<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

		for (const auto& extension : extensions)
		{
			std::string extensionName{ extension.extensionName };
			requiredExtensions.erase(
				std::remove(requiredExtensions.begin(), requiredExtensions.end(), extensionName),
				requiredExtensions.end()
			);
		}
			
		return requiredExtensions.empty();
	}

	void VulkanBackend::querySwapChainSupport(VkPhysicalDevice device)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &m_swapChainDetails->m_cap);

		uint32_t count{};
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &count, nullptr);
		if (count != 0)
		{
			m_swapChainDetails->m_formats.resize(count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &count, m_swapChainDetails->m_formats.data());
		}

		count = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &count, nullptr);
		if (count != 0)
		{
			m_swapChainDetails->m_presentModes.resize(count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &count, m_swapChainDetails->m_presentModes.data());
		}
	}

	VkSurfaceFormatKHR VulkanBackend::chooseSwapSurfaceFormat()
	{
		for (const auto& format : m_swapChainDetails->m_formats)
		{
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return format;
		}
		// just return first format for now
		return m_swapChainDetails->m_formats[0];
	}

	VkPresentModeKHR VulkanBackend::chooseSwapPresentMode()
	{
		for (const auto& presentMode : m_swapChainDetails->m_presentModes)
		{
			if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return presentMode;
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanBackend::chooseSwapExtent()
	{
		if (m_swapChainDetails->m_cap.currentExtent.width != std::numeric_limits<uint32_t>::max())
			return m_swapChainDetails->m_cap.currentExtent;
		else
		{
			Core::FrameBufferSize size{m_createInfo.m_window->getFraneBufferSize()};

			VkExtent2D extent = {
				static_cast<uint32_t>(size.m_width),
				static_cast<uint32_t>(size.m_height)
			};
			extent.width = std::clamp(extent.width, m_swapChainDetails->m_cap.minImageExtent.width, m_swapChainDetails->m_cap.maxImageExtent.width);
			extent.height = std::clamp(extent.height, m_swapChainDetails->m_cap.minImageExtent.height, m_swapChainDetails->m_cap.maxImageExtent.height);
			return extent;
		}
	}

	///////////////// VULKAN DEBUG ///////////////////////
	//////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanBackend::debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			Core::Logger::getInstance().logInfo(std::string{"Validaion layer: "} + pCallbackData->pMessage, __FILE__);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			Core::Logger::getInstance().logWarn(std::string{"Validaion layer: "} + pCallbackData->pMessage, __FILE__);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			Core::Logger::getInstance().logError(std::string{"Validaion layer: "} + pCallbackData->pMessage, __FILE__);
			break;
		}
		return VK_FALSE;
	}

	VkResult VulkanBackend::createDebugUtilsMessengerEXT(VkInstance instance, 
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) 
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		else 
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		
	}

	void VulkanBackend::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
	}
}