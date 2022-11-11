#pragma once
#include "../../libs/glad/include/glad/glad.h"
#include <stdint.h>
#include <iostream>

class Texture
{
public:
	Texture(uint32_t type);
	~Texture();

	void bind();
	void unbind();
	virtual void load() {};

protected:
	uint32_t m_type;
	uint32_t m_id;
};