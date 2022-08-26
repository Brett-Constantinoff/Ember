#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float moveSpeed, float rotationSpeed) :
    m_position{ position }, m_front{ front }, m_up{ up }, m_yaw{yaw}, m_pitch{pitch}, m_moveSpeed{moveSpeed}, m_rotationSpeed{rotationSpeed}
{
};

void Camera::move(GLFWwindow* win, float dt)
{
    updateFront();
    updatePosition(win, dt);
    updateEuler(win, dt);
}

void Camera::updatePosition(GLFWwindow* win, float dt)
{
    const float cameraSpeed = m_moveSpeed * dt;

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_position += cameraSpeed * m_front;
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_position -= cameraSpeed * m_front;
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_position += glm::normalize(glm::cross(m_front, m_up)) * cameraSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_position += cameraSpeed * m_up;
    }
    if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
    {
        m_position -= cameraSpeed * m_up;
    }
}

void Camera::updateEuler(GLFWwindow* win, float dt)
{
    if (m_pitch >= 90.0f)
    {
        m_pitch = 90.0f;
    }
    if (m_pitch <= -90.0f)
    {
        m_pitch = -90.0f;
    }

    const float rotationSpeed = (m_rotationSpeed * dt) + 0.5f;

    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_yaw += rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_yaw -= rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_pitch += rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_pitch -= rotationSpeed;
    }
}

void Camera::updateFront(void)
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);
}

glm::mat4* Camera::getView(void)
{
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    return &m_view;
}