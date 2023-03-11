#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::update(float dt)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = m_createInfo.m_scene->getCamera()->getView();
		projection = m_createInfo.m_window->getPerspective();
		m_createInfo.m_scene->getShader()->use();

		m_createInfo.m_scene->getShader()->setMat4("model", model);
		m_createInfo.m_scene->getShader()->setMat4("projection", projection);
		m_createInfo.m_scene->getShader()->setMat4("view", view);

		m_createInfo.m_scene->getCamera()->move(m_createInfo.m_window->getContext(), dt);

		
	}

	void Renderer::render()
	{
		updateGui();
		glBindVertexArray(m_createInfo.m_scene->getCube());
		glDrawArrays(GL_TRIANGLES, 0, 36);
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