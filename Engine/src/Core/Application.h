#pragma once
#include "Layer.h"
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
    LayerStack* m_layerStack;
    Window* m_window;
    float m_lastFrame = 0.0f;
};