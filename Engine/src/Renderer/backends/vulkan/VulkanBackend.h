#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <optional>
#include <set>
#include <cstring>
#include <limits>
#include <algorithm>

#include "../RendererBackend.h"

namespace Ember::Renderer
{
	class VulkanBackend : public RendererBackend
	{
	public:
		VulkanBackend() = default;

	private:
		virtual void init(const RendererCreateInfo& createInfo);
		virtual void destroy();
		virtual void update(float dt);
		virtual void render();
		virtual void loadSkybox();
		virtual void renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh);
		virtual void renderSkybox();

		virtual void initMeshRenderData(const std::shared_ptr<Scene::Mesh>& mesh);
		virtual void initMeshTextures(const std::shared_ptr < Scene::Mesh>& mesh);
		virtual void loadMeshTexture(const std::string& texture);

	private:
		// vulkan structs (hacky way to have a private struct within class)
		struct QueueFamilyIndices;
		std::shared_ptr<QueueFamilyIndices> m_indices{nullptr};

		struct SwapChainSupportDetails;
		std::shared_ptr<SwapChainSupportDetails> m_swapChainDetails{nullptr};

		// vulkan creation
		void createInstance();
		void createDebugMessenger();
		void createPhysicalDevice();
		void createLogicalDevice();
		void createSurface();
		void createSwapChain();
		void createImageViews();

		// vulkan destruction
		void destroyDebugUtilsMessengerEXT(VkInstance instance,
			VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		// vulkan utils
		bool physicalDeviceSuitable(VkPhysicalDevice device);
		void getQueueFamilies(VkPhysicalDevice device);
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtenions();
		bool checkDeviceExtensionSupport(VkPhysicalDevice);
		void querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat();
		VkPresentModeKHR chooseSwapPresentMode();
		VkExtent2D chooseSwapExtent();

		// vulkan debug
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		VkResult createDebugUtilsMessengerEXT(VkInstance instance, 
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	private:
		const std::vector<const char*> m_validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	#if NDEBUG
		const bool m_enableValidatonLayers{ false };
	#else
		const bool m_enableValidationLayers{ true };
	#endif

		VkInstance m_instance{};
		VkDebugUtilsMessengerEXT m_debugMessenger{};
		VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };
		VkDevice m_logicalDevice{};
		VkQueue m_graphicsQueue{};
		VkQueue m_presentQueue{};
		VkSurfaceKHR m_surface{};
		VkSwapchainKHR m_swapChain{};
		std::vector<VkImage> m_swapChainImages{};
		VkFormat m_swapChainImageFormat{};
		VkExtent2D m_swapChainExtent{};
		std::vector<VkImageView> m_swapChainImageViews{};

		friend class Renderer;
	};
}