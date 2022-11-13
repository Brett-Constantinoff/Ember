#pragma once
#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D(uint32_t type, int32_t width, int32_t height);
	~Texture2D();

	void loadDepth();
};