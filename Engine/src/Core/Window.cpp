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


            // exit the app right away since if glfw isnt initialized, glad wont intialize and then
            // any opengl api call in the future will crash the app. Better to catch here than later
            if (!m_winID)
            {
                Logger::getInstance().logError(std::string{ "GLFW failed to initialize" }, __FILE__);
            }
            else
            {
                glfwMakeContextCurrent(m_winID);

                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                    Logger::getInstance().logError(std::string{ "GLAD failed to initialize" }, __FILE__);
                glfwSetFramebufferSizeCallback(m_winID, resizeOpenGLApi);
            }
        }
        else
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            m_winID = glfwCreateWindow(m_createInfo.m_width, m_createInfo.m_height, m_createInfo.m_label.c_str(), NULL, NULL);

            // see above comment
            if (!m_winID)
            {
                Logger::getInstance().logError(std::string{ "GLFW failed to initialize" }, __FILE__);
            }
        }
        Logger::getInstance().logInfo(std::string{"Window created successfully"}, __FILE__);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_winID);
        glfwTerminate();
        Logger::getInstance().logInfo(std::string{"Window destroyed successfully"}, __FILE__);
    }

    WindowApi Window::getApi() const
    {
        return m_createInfo.m_api;
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

    WindowExtensions Window::getExtensions()
    {
        uint32_t glfwExtensionCount{ 0 };
        return { glfwGetRequiredInstanceExtensions(&glfwExtensionCount), glfwExtensionCount };
    }

    void Window::resizeOpenGLApi(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}


