#include "Scene.h"

Scene::~Scene()
{
	std::cout << "Destroying Scene\n";
	for (auto renderable : m_renderables)
	{
		delete renderable;
	}
	m_renderables.clear();
}

void Scene::addRenderable(SceneObject* obj)
{
	m_renderables.push_back(obj);
}

std::vector<SceneObject*>* Scene::getRenderables()
{
	return &m_renderables;
}