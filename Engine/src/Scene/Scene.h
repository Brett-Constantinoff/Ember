#pragma once

#include "SceneObject.h"
#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene();

	void addRenderable(SceneObject* obj);
	std::vector<SceneObject*>* getRenderables();
	
private:
	std::vector<SceneObject*> m_renderables;
};