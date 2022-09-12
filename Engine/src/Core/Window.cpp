#include "Window.h"

Window::Window(const std::string& label, uint32_t width, uint32_t height) :
    m_label{ label }, m_width{ width }, m_height{ height }
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_winID = glfwCreateWindow(m_width, m_height, m_label.c_str(), NULL, NULL);
    if (!m_winID)
    {
        std::cout << "ERROR CREATING OPENGL WINDOW!" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_winID);
    glfwSetFramebufferSizeCallback(m_winID, resize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_winID, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Window::~Window()
{
    glfwDestroyWindow(m_winID);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

GLFWwindow** Window::getContext()
{
    return &m_winID;
}

uint32_t Window::getWidth()
{
    return m_width;
}

uint32_t Window::getHeight()
{
    return m_height;
}

bool Window::isOpen()
{
    bool result = !glfwWindowShouldClose(m_winID);
    return result;
}

void Window::update()
{
    glfwSwapBuffers(m_winID);
    glfwPollEvents();
}
