#pragma once
#include "../core//Glm.h"
#include "../core/OpenGL.h"

namespace Ember::Scene
{
    struct CameraCreateInfo
    {
        GLFWwindow* m_winContext{};
        glm::vec3 m_pos{};
        glm::vec3 m_front{};
        glm::vec3 m_worldUp{};
        glm::vec3 m_up{};
        glm::vec3 m_right{};
        float m_yaw{};
        float m_pitch{};
        float m_speed{};
        float m_zoom{};
        float m_sensitivity{};
        float m_near{};
        float m_far{};
    };

    // GLOBAL VARIABLES BAD!!!
    static float xPos{};
    static float yPos{};
    static float xOffset{};
    static float yOffset{};
    static float zoom{};
    static bool firstMoved{ true };
 

    class Camera
    {
    public:
        Camera(const CameraCreateInfo& createInfo);
        ~Camera();

        void move(float dt);
        glm::mat4& getView();
        glm::vec3& getPos();
        glm::vec3& getFront();
        float getNear() const;
        float getFar() const;
        float getZoom() const;

    private:
        void updateVectors();
        void processKeyBoard(float dt);
        void processMouse();
        void processZoom();
        static void mouseCallBack(GLFWwindow* win, double xpos, double ypos);
        static void scrollCallBack(GLFWwindow* win, double xOffset, double yOffset);


    private:
        CameraCreateInfo m_createInfo;
        glm::mat4 m_view;
    };
}
