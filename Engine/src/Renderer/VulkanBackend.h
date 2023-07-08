#pragma once
#include "RendererBackend.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <optional>

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

	private:
		// vulkan structs (hacky way to have a private struct within class)
		struct QueueFamilyIndices;
		std::shared_ptr<QueueFamilyIndices> m_indices{nullptr};

		// vulkan creation
		void createInstance();
		void createPhysicalDevice();
		void createLogicalDevice();

		// vulkan utils
		bool physicalDeviceSuitable(VkPhysicalDevice device);
		void getQueueFamilies(VkPhysicalDevice device);

	private:
		VkInstance m_instance{};
		VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };
		VkDevice m_logicalDevice{};
		VkQueue m_graphicsQueue{};
	};
}