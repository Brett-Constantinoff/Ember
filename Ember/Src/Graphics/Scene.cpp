#include "Scene.h"

Scene::Scene(SceneSettings settings) :
	m_settings{settings}
{
}

Scene::~Scene()
{
	while (m_meshes.size() > 0)
	{
		m_meshes.pop_back();
	}

	while (m_cameras.size() > 0)
	{
		m_cameras.pop_back();
	}
}

void Scene::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}

void Scene::addCamera(Camera* camera, bool mainCam)
{
	if (mainCam)
	{
		m_mainCamera = camera;
	}
	m_cameras.push_back(camera);
}

void Scene::update(GLFWwindow* win, float dt)
{
	m_mainCamera->move(win, dt);
	m_view = *m_mainCamera->getView();
	m_proj = glm::perspective(m_settings.m_fov, m_settings.m_asspect, m_settings.m_near, m_settings.m_far);
}

void Scene::render()
{

	for (Mesh* m : m_meshes)
	{
		m->updateUniforms(m_proj, m_view);
		m->render();
	}
}