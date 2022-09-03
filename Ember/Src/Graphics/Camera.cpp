#include "Camera.h"

Camera::Camera(CameraProps props) :
   m_props{props}
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
    const float cameraSpeed = m_props.m_moveSpeed * dt;

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_props.m_position += cameraSpeed * m_props.m_front;
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_props.m_position -= cameraSpeed * m_props.m_front;
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_props.m_position -= glm::normalize(glm::cross(m_props.m_front, m_props.m_up)) * cameraSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_props.m_position += glm::normalize(glm::cross(m_props.m_front, m_props.m_up)) * cameraSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_props.m_position += cameraSpeed * m_props.m_up;
    }
    if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
    {
        m_props.m_position -= cameraSpeed * m_props.m_up;
    }
}

void Camera::updateEuler(GLFWwindow* win, float dt)
{
    if (m_props.m_pitch > 89.0f)
    {
        m_props.m_pitch = 89.0f;
    }
    if (m_props.m_pitch < -89.0f)
    {
        m_props.m_pitch = -89.0f;
    }

    const float rotationSpeed = (m_props.m_rotationSpeed * dt) + 0.5f;

    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_props.m_yaw += rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_props.m_yaw -= rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_props.m_pitch += rotationSpeed;
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_props.m_pitch -= rotationSpeed;
    }
}

void Camera::updateFront(void)
{
    m_props.m_front.x = cos(glm::radians(m_props.m_yaw)) * cos(glm::radians(m_props.m_pitch));
    m_props.m_front.y = sin(glm::radians(m_props.m_pitch));
    m_props.m_front.z = sin(glm::radians(m_props.m_yaw)) * cos(glm::radians(m_props.m_pitch));
    m_props.m_front = glm::normalize(m_props.m_front);
}

glm::mat4* Camera::getView(void)
{
    m_props.m_view = glm::lookAt(m_props.m_position, m_props.m_position + m_props.m_front, m_props.m_up);
    return &m_props.m_view;
}

glm::vec3* Camera::getPos(void)
{
    return &m_props.m_position;
}