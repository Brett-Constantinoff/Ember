#pragma once
#include "../../libs/glad/include/glad/glad.h"
#include <stdint.h>
#include <cstring>

class VertexArray
{
public:
    VertexArray();
    virtual void bind();
    virtual void unBind();
    void setLayout(uint32_t numPerAttrib, uint32_t type, uint32_t normalized, size_t stride, void* start);

private:
    uint32_t m_id;
    uint32_t m_layoutPos = 0;
};