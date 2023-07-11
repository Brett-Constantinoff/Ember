#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <optional>
#include <set>

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

		// vulkan creation
		void createInstance();
		void createPhysicalDevice();
		void createLogicalDevice();
		void createSurface();

		// vulkan utils
		bool physicalDeviceSuitable(VkPhysicalDevice device);
		void getQueueFamilies(VkPhysicalDevice device);

	private:
		VkInstance m_instance{};
		VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };
		VkDevice m_logicalDevice{};
		VkQueue m_graphicsQueue{};
		VkQueue m_presentQueue{};
		VkSurfaceKHR m_surface{};


		friend class Renderer;
	};
}