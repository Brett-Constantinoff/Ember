#pragma once
#include "SceneObject.h"
#include "../Renderer/Material.h"
#include "../Renderer/TextureCubeMap.h"
#include <vector>

class SkyBox : public SceneObject
{
public:
	SkyBox(const char* name, const Material& material, std::vector<const char*>& files);
	~SkyBox();
	TextureCubeMap* getCubeMap();

private:
	TextureCubeMap m_texture;
};