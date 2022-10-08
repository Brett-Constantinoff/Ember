#pragma once
#include "../../libs/glad/include/glad/glad.h"
#include <stdint.h>
#include <cstring>

class Buffer
{
public:
	Buffer(uint32_t bufferType);
	~Buffer();

	virtual void bind() {};
	virtual void unBind() {};

protected:
	uint32_t m_bufferId;
	uint32_t m_bufferType;
};