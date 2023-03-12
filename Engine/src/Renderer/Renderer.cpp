#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }
	{
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::update(double dt)
	{
		glClearColor(m_createInfo.m_backgroundCol[0], m_createInfo.m_backgroundCol[1], m_createInfo.m_backgroundCol[2], m_createInfo.m_backgroundCol[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateGui();
		m_createInfo.m_scene->getCamera()->move(m_createInfo.m_window->getContext(), dt);
	}

	void Renderer::render()
	{
		auto objects = m_createInfo.m_scene->getEntities();
		for (const auto& e : objects)
		{
			// only render the physical objetcs in the scene
			if (e->getType() == Ember::Scene::EntityType::RENDERABLE)
			{
				// get uniforms
				glm::mat4 model{ 1.0f };
				glm::mat4 proj{ m_createInfo.m_window->getPerspective() };
				glm::mat4 view{ m_createInfo.m_scene->getCamera()->getView() };

				// update the uniforms
				Shader* sceneShader{ m_createInfo.m_scene->getShader() };
				sceneShader->use();
				sceneShader->setMat4("model", model);
				sceneShader->setMat4("projection", proj);
				sceneShader->setMat4("view", view);
				sceneShader->setVec3("uViewPos", m_createInfo.m_scene->getCamera()->getPos());

				// render the object
				Ember::Scene::RenderData data{ e->getRenderData() };
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