#include "Application.h"

Application::Application(const std::string& label, uint32_t width, uint32_t height) :
    m_label{label}
{
    m_layerStack = new LayerStack();
    m_window = new Window(label, width, height);
    std::cout << "Creating " << label << std::endl;

    // create an imgui layer but dont add to layer stack
    m_imguiLayer = new ImguiLayer("Imgui Layer", m_window);
}

Application::~Application()
{
    delete m_window;
    delete m_imguiLayer;
    delete m_layerStack;
    std::cout << "Destorying " << m_label << std::endl;
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

        m_imguiLayer->onUpdate(dt);
        m_layerStack->updateLayers(dt);
        m_imguiLayer->onRender();

        m_window->update();
    }
}