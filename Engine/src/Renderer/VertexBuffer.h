#pragma once
#include "Buffer.h"

class VertexBuffer : public Buffer
{
public:
    VertexBuffer(uint32_t type);

    virtual void bind();
    virtual void unBind();
    void setData(size_t bytes, void* data, uint32_t usage);
};