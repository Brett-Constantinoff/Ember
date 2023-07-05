#pragma once
#include "RendererBackend.h"
#include <vulkan/vulkan.h>

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
	};
}