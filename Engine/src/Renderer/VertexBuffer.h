#pragma once
#include "Buffer.h"

namespace Ember
{
    namespace Renderer
    {
        class VertexBuffer : public Buffer
        {
        public:
            VertexBuffer(uint32_t type);
            virtual ~VertexBuffer();

            virtual void bind();
            virtual void unBind();
            virtual void generate();
            void setData(size_t bytes, void* data, uint32_t usage);
        };
    }
}