#pragma once
#include "../Math/glm.hpp"
#include "../Math/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(
        glm::vec3 position = { 0.0f, 0.0f, 0.0f },
        glm::vec3 front = { 0.0f, 0.0f, -1.0f },
        glm::vec3 up = { 0.0f, 1.0f, 0.0f },
        float yaw = -90.0f,
        float pitch = 0.0f,
        float moveSpeed = 3.0f,
        float rotationSpeed = 45.0f
    );
    void move(GLFWwindow* win, float dt);
    glm::mat4* getView(void);

private:
    void updatePosition(GLFWwindow* win, float dt);
    void updateEuler(GLFWwindow* win, float dt);
    void updateFront(void);

private:
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    float m_yaw;
    float m_pitch;
    float m_moveSpeed;
    float m_rotationSpeed;
};