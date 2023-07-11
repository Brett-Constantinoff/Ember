#pragma once
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <functional>

#include "Logger.h"

namespace Ember::Core
{
    enum class WindowApi
    {
        OpenGL, 
        Vulkan
    };

    struct WindowCreateInfo
    {
        std::string m_label{};
        int32_t m_width{};
        int32_t m_height{};
        WindowApi m_api{};
    };

    struct WindowExtensions
    {
        const char** m_extensions{};
        uint32_t m_count{};
    };

    class Window
    {
    public:
        Window(const WindowCreateInfo& createInfo);
        ~Window();

        GLFWwindow** getContext();
        WindowApi getApi() const;
        int32_t getWidth() const;
        int32_t getHeight() const;
        void update();
        bool isOpen();
        void setViewPort(int32_t width, int32_t height);
        void setViewPort();
        WindowExtensions getExtensions();

    private:
        static void resizeOpenGLApi(GLFWwindow* window, int width, int height);

    private:
        GLFWwindow* m_winID;
        WindowCreateInfo m_createInfo;
    };
}