#pragma once
#include "Callbacks.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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