#pragma once
#include "../core//Glm.h"
#include "../core/OpenGL.h"

namespace Ember::Scene
{
    struct CameraCreateInfo
    {
        glm::vec3 m_pos{};
        glm::vec3 m_front;
        glm::vec3 m_up{};
        float m_yaw{};
        float m_pitch{};
    };

    class Camera
    {
    public:
        Camera(const CameraCreateInfo& createInfo);
        ~Camera();

        void move(GLFWwindow** window, double dt);
        glm::mat4& getView();
        glm::vec3& getPos();

    private:
        CameraCreateInfo m_createInfo;
        glm::mat4 m_view;
    };
}
