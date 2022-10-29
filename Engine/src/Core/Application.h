#pragma once
#include "Layer.h"
#include "ImguiLayer.h"
#include "LayerStack.h"
#include "Window.h"
#include <string.h>

class Application
{
public:
    Application(const std::string& label = "Application", uint32_t width = 1280, uint32_t height = 720);
    virtual ~Application() = 0;

    void start();
    void pushLayer(Layer* layer);

private:
    LayerStack m_layerStack;
    std::unique_ptr<ImguiLayer> m_imguiLayer;
    Window m_window;
    const std::string m_label;
    float m_lastFrame;
};