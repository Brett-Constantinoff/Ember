#pragma once
#include "Texture.h"
#include "../../libs/stb/stb_image.h"
#include <iostream>
#include <vector>

class TextureCubeMap : public Texture
{
public:
	TextureCubeMap(uint32_t m_type, std::vector<const char*>& files);
	~TextureCubeMap();

	virtual void load();

private:
	std::vector<const char*> m_files;
};