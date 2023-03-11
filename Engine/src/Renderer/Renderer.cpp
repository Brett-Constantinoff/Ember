#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }
	{
		if (m_createInfo.m_imguiEnabled)
			initImgui();
	}

	Renderer::~Renderer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
		updateImgui();

		glBindVertexArray(m_createInfo.m_scene->getCube());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		renderImgui();
	}

	void Renderer::initImgui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(*m_createInfo.m_window->getContext(), true);
		ImGui_ImplOpenGL3_Init("#version 150");
	}

	void Renderer::updateImgui()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::renderImgui()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}