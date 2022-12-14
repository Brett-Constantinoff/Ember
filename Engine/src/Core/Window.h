#pragma once
#include "../../libs/windowCreation/include/GLFW/glfw3.h"
#include "../../libs/glad/include/glad/glad.h"
#include "../../libs/math/glm/glm.hpp"
#include "../../libs/math/glm/gtc/matrix_transform.hpp"
#include "../../libs/math/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

namespace Ember
{
    namespace Core
    {
        class Window
        {
        public:
            Window(const std::string& label, uint32_t width, uint32_t height);
            ~Window();

            GLFWwindow* getContext();
            uint32_t getWidth();
            uint32_t getHeight();
            glm::mat4 getPerspective();
            void update();
            bool isOpen();
            void setViewPort(int32_t width, int32_t height);
            void setViewPort();

        private:
            GLFWwindow* m_winID;
            const std::string& m_label;
            uint32_t m_width;
            uint32_t m_height;
            float m_fov = 45.0f;
            float m_near = 0.1f;
            float m_far = 500.0f;
        };
    }
}