#pragma once
#include "../../libs/math/glm/glm.hpp"
#include "../../libs/math/glm/gtc/matrix_transform.hpp"
#include "../../libs/math/glm/gtc/type_ptr.hpp"
#include "../../libs/windowCreation/include/GLFW/glfw3.h"
#include "../../libs/glad/include/glad/glad.h"
namespace Ember
{
    namespace Renderer
    {
        class Camera
        {
        public:
            Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
            void move(GLFWwindow* win, float dt);
            glm::mat4* getView();
            glm::vec3* getPos();

        private:
            glm::mat4 m_view;
            glm::vec3 m_position;
            glm::vec3 m_front;
            glm::vec3 m_up;
            float m_yaw;
            float m_pitch;
        };
    }
}
