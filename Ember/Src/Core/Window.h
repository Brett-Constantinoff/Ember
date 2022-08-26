#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Gui/gui.h"
#include "Callbacks.h"

class Window
{
public:
    Window(const std::string& label, uint32_t width, uint32_t height);
    ~Window();

    GLFWwindow** getContext();
    uint32_t getWidth();
    uint32_t getHeight();
    void update();
    bool isOpen();


private:
    GLFWwindow* m_winID;
    const std::string& m_label;
    uint32_t m_width;
    uint32_t m_height;
};
