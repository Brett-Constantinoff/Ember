#include "Scene.h"

Scene::Scene(SceneSettings settings) :
	m_settings{settings}
{
    // create skybox as a custom mesh
    std::vector<float> vertexPositions = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    Geometry geo(vertexPositions, {}, {}, {});
    m_skybox = new Mesh(geo, {
        {".\\Src\\Assets\\Textures\\MountainSkybox\\right.jpg",
        ".\\Src\\Assets\\Textures\\MountainSkybox\\left.jpg",
        ".\\Src\\Assets\\Textures\\MountainSkybox\\top.jpg",
        ".\\Src\\Assets\\Textures\\MountainSkybox\\bottom.jpg",
        ".\\Src\\Assets\\Textures\\MountainSkybox\\front.jpg",
        ".\\Src\\Assets\\Textures\\MountainSkybox\\back.jpg"} });
}

Scene::~Scene()
{
    for (Mesh* mesh : m_meshes)
    {
        delete mesh;
    }
    m_meshes.clear();

    for (Camera* camera : m_cameras)
    {
        delete camera;
    }
    m_cameras.clear();

    delete m_dirLightCaster;
    delete m_skybox;
}

void Scene::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}

void Scene::addDirLightCaster(LightCaster<DirectionalLight>* lightCaster)
{
    m_dirLightCaster = lightCaster;
}

void Scene::addCamera(Camera* camera, bool mainCam)
{
	if (mainCam)
	{
		m_mainCamera = camera;
	}
	m_cameras.push_back(camera);
}

void Scene::update(float dt)
{
	m_mainCamera->move(*m_settings.m_window->getContext(), dt);
	m_view = *m_mainCamera->getView();

    const float fov = glm::radians(45.0f);
    const float aspect = static_cast<float>(m_settings.m_window->getWidth()) / static_cast<float>(m_settings.m_window->getHeight());
    const float znear = 0.1f;
    const float zfar = 100.0f;
	m_proj = glm::perspective(fov, aspect , znear, zfar);
}

glm::mat4* Scene::getView(void)
{
    return &m_view;
}

glm::mat4* Scene::getProj(void)
{
    return &m_proj;
}

std::vector<Mesh*>* Scene::getMeshes(void)
{
    return &m_meshes;
}

LightCaster<DirectionalLight>* Scene::getDirLightCaster(void)
{
    return m_dirLightCaster;
}

Mesh* Scene::getSkybox(void)
{
    return m_skybox;
}

Camera* Scene::getMainCam(void)
{
    return m_mainCamera;
}