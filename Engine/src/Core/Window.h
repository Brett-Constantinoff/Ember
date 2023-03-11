#pragma once
#include "OpenGL.h"
#include "Glm.h"

#include <iostream>
#include <string>
#include <functional>

namespace Ember::Core
{
    struct WindowCreateInfo
    {
        std::string m_label{};
        int32_t m_width{};
        int32_t m_height{};
        float m_fov{};
        float m_near{};
        float m_far{};

        std::string m_api{};
    };

    class Window
    {
    public:
        Window(const WindowCreateInfo& createInfo);
        ~Window();

        GLFWwindow** getContext();
        int32_t getWidth();
        int32_t getHeight();
        glm::mat4& getPerspective();
        void update();
        bool isOpen();
        void setViewPort(int32_t width, int32_t height);
        void setViewPort();

    private:
        static void resizeOpenGLApi(GLFWwindow* window, int width, int height);

    private:
        GLFWwindow* m_winID;
        WindowCreateInfo m_createInfo;
        glm::mat4 m_perspective;
    };
}