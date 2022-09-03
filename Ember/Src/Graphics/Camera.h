#pragma once
#include "../Math/glm.hpp"
#include "../Math/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

struct CameraProps
{
    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_front = { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_up = { 0.0f, 1.0f, 0.0f };
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_moveSpeed = 3.0f;
    float m_rotationSpeed = 45.0f;
    glm::mat4 m_view = glm::mat4(1.0f);
};

class Camera
{
public:
    Camera(CameraProps props);
    void move(GLFWwindow* win, float dt);
    glm::mat4* getView(void);
    glm::vec3* getPos(void);

private:
    void updatePosition(GLFWwindow* win, float dt);
    void updateEuler(GLFWwindow* win, float dt);
    void updateFront(void);

private:
    CameraProps m_props;
};