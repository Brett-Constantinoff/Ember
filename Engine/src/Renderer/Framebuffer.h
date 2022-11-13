#pragma once
#include "Buffer.h"
#include "Texture.h"

class Framebuffer : public Buffer
{
public:
	Framebuffer(uint32_t type);
	virtual ~Framebuffer();

	virtual void bind();
	virtual void unbind();
	virtual void generate();
	void attachDepthTex(Texture& depthTex);
};