#include "VulkanBackend.h"

namespace Ember::Renderer
{
	void VulkanBackend::init(const RendererCreateInfo& createInfo)
	{

	}

	void VulkanBackend::destroy()
	{

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
}