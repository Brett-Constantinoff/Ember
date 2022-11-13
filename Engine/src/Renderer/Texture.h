#pragma once
#include "../../libs/glad/include/glad/glad.h"
#include <stdint.h>
#include <iostream>

class Texture
{
public:
	Texture(uint32_t type);
	Texture(uint32_t type, int32_t width, int32_t height);
	~Texture();

	void bind();
	void unbind();
	uint32_t getId();
	uint32_t getType();
	virtual void load() {};

protected:
	uint32_t m_type;
	uint32_t m_id;
	int32_t m_width;
	int32_t m_height;
};