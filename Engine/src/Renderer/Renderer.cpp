#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_perspective{}, m_view{}
	{
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::update(float dt)
	{
		glClearColor(m_createInfo.m_backgroundCol[0], m_createInfo.m_backgroundCol[1], m_createInfo.m_backgroundCol[2], m_createInfo.m_backgroundCol[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	void Renderer::render()
	{
		auto objects = m_createInfo.m_scene->getEntities();
		for (const auto& e : objects)
		{
			// only render the physical objetcs in the scene
			if (e->getType() == Ember::Scene::EntityType::RENDERABLE)
			{
				// update transforms
				Ember::Scene::TransformData transforms{ e->getMesh().getTransformData()};
				glm::mat4 model{ 1.0f };

				model = glm::translate(model, transforms.m_translation) *
					glm::translate(model, transforms.m_centroid) *
					transforms.m_rotate *
					glm::translate(model, -transforms.m_centroid) *
					glm::scale(model, transforms.m_scale);

					
				// update the uniforms
				Shader* sceneShader{ m_createInfo.m_scene->getShader() };
				sceneShader->use();
				sceneShader->setMat4("model", model);
				sceneShader->setMat4("projection", m_perspective);
				sceneShader->setMat4("view", m_view);
				sceneShader->setVec3("uViewPos", m_createInfo.m_scene->getCamera()->getPos());
				Ember::Scene::RenderData data{ e->getMesh().getRenderData() };
				
				// render the object
				glBindVertexArray(data.m_vao);
				glDrawElements(GL_TRIANGLES, data.m_indices.size(), GL_UNSIGNED_INT, 0);
			}
		}

		// render our gui
		renderGui();
	}

	void Renderer::updateGui()
	{
		if (m_createInfo.m_guiEnabled)
			m_createInfo.m_gui->update();
	}

	void Renderer::renderGui()
	{
		if (m_createInfo.m_guiEnabled)
			m_createInfo.m_gui->render();
	}
}