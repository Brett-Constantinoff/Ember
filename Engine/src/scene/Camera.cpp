#include "Camera.h"

namespace Ember::Scene
{
    Camera::Camera(const CameraCreateInfo& createInfo) :
        m_createInfo{ createInfo }, m_view{ glm::mat4(1.0f)}
    {

    };

    Camera::~Camera()
    {

    }

    void Camera::move(GLFWwindow** window, float dt)
    {
        m_createInfo.m_front.x = cos(glm::radians(m_createInfo.m_yaw)) * cos(glm::radians(m_createInfo.m_pitch));
        m_createInfo.m_front.y = sin(glm::radians(m_createInfo.m_pitch));
        m_createInfo.m_front.z = sin(glm::radians(m_createInfo.m_yaw)) * cos(glm::radians(m_createInfo.m_pitch));
        m_createInfo.m_front = glm::normalize(m_createInfo.m_front);

        const float cameraSpeed = 3.0f * dt;
        GLFWwindow* win = *window;

        if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
            m_createInfo.m_pos += cameraSpeed * m_createInfo.m_front;
        
        if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
            m_createInfo.m_pos -= cameraSpeed * m_createInfo.m_front;
        
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
            m_createInfo.m_pos -= glm::normalize(glm::cross(m_createInfo.m_front, m_createInfo.m_up)) * cameraSpeed;
        
        if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
            m_createInfo.m_pos += glm::normalize(glm::cross(m_createInfo.m_front, m_createInfo.m_up)) * cameraSpeed;
        
        if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
            m_createInfo.m_yaw += 2.0f;
        
        if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
            m_createInfo.m_yaw -= 2.0f;
        
        if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
            m_createInfo.m_pitch += 2.0f;
        
        if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
            m_createInfo.m_pitch -= 2.0f;
    }

    glm::mat4& Camera::getView()
    {
        m_view = glm::lookAt(m_createInfo.m_pos, m_createInfo.m_pos + m_createInfo.m_front, m_createInfo.m_up);
        return m_view;
    }

    glm::vec3& Camera::getPos()
    {
        return m_createInfo. m_pos;
    }  
}