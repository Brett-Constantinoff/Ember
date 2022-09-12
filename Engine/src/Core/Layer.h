#pragma once
#include "Window.h"
#include <string>

class Layer
{
public:
    Layer(const char* name = "Layer");
    virtual ~Layer() = default;

    virtual void onAttach(Window* win) {};
    virtual void onDetach() {};
    virtual void onUpdate(float dt) {};
    virtual void onRender() {};
    virtual void onImguiRender() {};

protected:
    const char* m_name;
};