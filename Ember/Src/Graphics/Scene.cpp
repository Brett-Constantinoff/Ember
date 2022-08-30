#include "Scene.h"

Scene::Scene(SceneSettings settings) :
	m_settings{settings}
{
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

    delete m_skybox;
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

void Scene::addSkybox(std::vector<const char*> files)
{
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

    Geometry geo(vertexPositions, {}, {});
    m_skybox = new Mesh(geo, { ".\\Src\\Shaders\\skyboxShader.hlsl", files });
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

void Scene::renderSkybox()
{
    glm::mat4 view = glm::mat4(glm::mat3(m_view));
    m_skybox->updateUniforms(m_proj, view);
    m_skybox->render();
}