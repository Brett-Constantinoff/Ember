#include "Window.h"

namespace Ember::Core
{
    Window::Window(const WindowCreateInfo& createInfo) :
        m_createInfo{createInfo}
    {
        glfwInit();

        if (createInfo.m_api == WindowApi::OpenGL)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_winID = glfwCreateWindow(m_createInfo.m_width, m_createInfo.m_height, m_createInfo.m_label.c_str(), NULL, NULL);

            if (!m_winID)
                throw::std::runtime_error{ "ERROR::CANNOT CREATE GLFW WINDOW CONTEXT!" };

            glfwMakeContextCurrent(m_winID);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                throw::std::runtime_error{ "ERROR::CANNOT INITIALIZE GLEW!" };

            glfwSetFramebufferSizeCallback(m_winID, resizeOpenGLApi);
        }
        else
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            m_winID = glfwCreateWindow(m_createInfo.m_width, m_createInfo.m_height, m_createInfo.m_label.c_str(), NULL, NULL);

            if (!m_winID)
                throw::std::runtime_error{ "ERROR::CANNOT CREATE GLFW WINDOW CONTEXT!" };
        }

    }

    Window::~Window()
    {
        glfwDestroyWindow(m_winID);
        glfwTerminate();
    }

    GLFWwindow** Window::getContext()
    {
        return &m_winID;
    }

    int32_t Window::getWidth() const
    {
        return m_createInfo.m_width;
    }

    int32_t Window::getHeight() const
    {
        return m_createInfo.m_height;
    }

    bool Window::isOpen()
    {
        return !glfwWindowShouldClose(m_winID);
    }

    void Window::update()
    {
        glfwSwapBuffers(m_winID);
        glfwPollEvents();
    }

    void Window::setViewPort(int32_t width, int32_t height)
    {
        glViewport(0, 0, width, height);
    }

    void Window::setViewPort()
    {
        int32_t width;
        int32_t height;

        glfwGetFramebufferSize(m_winID, &width, &height);
        glViewport(0, 0, width, height);
    }

    void Window::resizeOpenGLApi(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}


