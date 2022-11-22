#pragma once
#include <cstring>
#include <stdint.h>
#include "../../libs/glad/include/glad/glad.h"

namespace Ember
{
    namespace Renderer
    {
        class VertexArray
        {
        public:
            VertexArray();
            virtual void bind();
            virtual void unBind();
            void setLayout(uint32_t numPerAttrib, uint32_t type, uint32_t normalized, GLsizei stride, void* start);

        private:
            uint32_t m_id;
            uint32_t m_layoutPos;
        };
    }
}