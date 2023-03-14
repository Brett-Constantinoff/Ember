#include "Camera.h"

namespace Ember::Scene
{
    Camera::Camera(const CameraCreateInfo& createInfo) :
        m_createInfo{ createInfo }, m_view{ glm::mat4(1.0f)}
    {
        updateVectors();
        
        // set the mouse callback to capture mouse coordinates
        glfwSetCursorPosCallback(m_createInfo.m_winContext, mouseCallBack);

        // set a scroll call back so we can zoom the camera
        zoom = m_createInfo.m_zoom;
        glfwSetScrollCallback(m_createInfo.m_winContext, scrollCallBack);

        // enable this to hide the mouse
        //glfwSetInputMode(m_createInfo.m_winContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    };

    Camera::~Camera()
    {

    }

    void Camera::move(float dt)
    {
        processKeyBoard(dt);
        processMouse();
        processZoom();
    }

    glm::mat4& Camera::getView()
    {
        m_view = glm::lookAt(m_createInfo.m_pos, m_createInfo.m_pos + m_createInfo.m_front, m_createInfo.m_up);
        return m_view;
    }

    glm::vec3& Camera::getPos()
    {
        return m_createInfo.m_pos;
    }  

    glm::vec3& Camera::getFront()
    {
        return m_createInfo.m_front;
    }

    float Camera::getNear() const
    {
        return m_createInfo.m_near;
    }

    float Camera::getFar() const
    {
        return m_createInfo.m_far;
    }

    float Camera::getZoom() const
    {
        return m_createInfo.m_zoom;
    }

    void Camera::updateVectors()
    {
        glm::vec3 front{};
        front.x = cos(glm::radians(m_createInfo.m_yaw)) * cos(glm::radians(m_createInfo.m_pitch));
        front.y = sin(glm::radians(m_createInfo.m_pitch));
        front.z = sin(glm::radians(m_createInfo.m_yaw)) * cos(glm::radians(m_createInfo.m_pitch));

        m_createInfo.m_front = glm::normalize(front);
        m_createInfo.m_right = glm::normalize(glm::cross(m_createInfo.m_front, m_createInfo.m_worldUp));
        m_createInfo.m_up = glm::normalize(glm::cross(m_createInfo.m_right, m_createInfo.m_front));
    }

    void Camera::processKeyBoard(float dt)
    {
        float velocity{ dt * m_createInfo.m_speed };

        if (glfwGetKey(m_createInfo.m_winContext, GLFW_KEY_W) == GLFW_PRESS)
            m_createInfo.m_pos += velocity * m_createInfo.m_front;

        if (glfwGetKey(m_createInfo.m_winContext, GLFW_KEY_S) == GLFW_PRESS)
            m_createInfo.m_pos -= velocity * m_createInfo.m_front;

        if (glfwGetKey(m_createInfo.m_winContext, GLFW_KEY_A) == GLFW_PRESS)
            m_createInfo.m_pos -= m_createInfo.m_right * velocity;

        if (glfwGetKey(m_createInfo.m_winContext, GLFW_KEY_D) == GLFW_PRESS)
            m_createInfo.m_pos += m_createInfo.m_right * velocity;
    }

    void Camera::processMouse()
    {
        if (glfwGetMouseButton(m_createInfo.m_winContext, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            // sensitivity
            xOffset *= m_createInfo.m_sensitivity;
            yOffset *= m_createInfo.m_sensitivity;

            // update angles
            m_createInfo.m_yaw += xOffset;
            m_createInfo.m_pitch += yOffset;

            // clamp pitch
            if (m_createInfo.m_pitch > 89.0f)
                m_createInfo.m_pitch = 89.0f;
            if (m_createInfo.m_pitch < -89.0f)
                m_createInfo.m_pitch = -89.0f;

            // update vectors with new angles
            updateVectors();
        }
    }

    void Camera::processZoom()
    {
        m_createInfo.m_zoom = zoom;
    }

    void Camera::mouseCallBack(GLFWwindow* window, double xpos, double ypos)
    {
        float x{ static_cast<float>(xpos) };
        float y{ static_cast<float>(ypos) };

        // dont jump when camera first moves
        if (firstMoved)
        {
            xPos = x;
            xPos = y;
            firstMoved = false;
        }

        // calculate the offset from the old positon to the new
        xOffset = x - xPos;
        yOffset =  yPos - y;

        // update old positon
        xPos = x;
        yPos = y;
    }

    void Camera::scrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
    {
        // we only care about the y value
        zoom -= static_cast<float>(yOffset);
    }
}