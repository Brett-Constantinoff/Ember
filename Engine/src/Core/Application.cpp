#include "Application.h"

Application::Application(const std::string& label, uint32_t width, uint32_t height)
{
    m_layerStack = new LayerStack();
    m_window = new Window(label, width, height);
}

Application::~Application()
{
    delete m_window;
    delete m_layerStack;
}

void Application::pushLayer(Layer* layer)
{
    m_layerStack->push(layer, m_window);
}

void Application::start()
{
    while (m_window->isOpen())
    {
        float currFrame = static_cast<float>(glfwGetTime());
        float dt = currFrame - m_lastFrame;
        m_lastFrame = currFrame;

        //render
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_layerStack->updateLayers(dt);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window->update();
    }
}