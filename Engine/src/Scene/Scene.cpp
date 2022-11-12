#include "Scene.h"

Scene::Scene()
{
	glEnable(GL_DEPTH_TEST);
}

Scene::~Scene()
{
	std::cout << "Destroying Scene\n";
	for (auto renderable : m_renderables)
	{
		delete renderable;
	}
	m_renderables.clear();
	delete m_camera;
	delete m_skybox;
}

void Scene::addRenderable(SceneObject* obj)
{
	m_renderables.push_back(obj);
}

void Scene::addCamera(Camera* camera)
{
	m_camera = camera;
}

void Scene::addContext(Window* window)
{
	m_win = window;
}

void Scene::addSkyBox(SkyBox* skybox)
{
	m_skybox = skybox;
}

std::vector<SceneObject*>* Scene::getRenderables()
{
	return &m_renderables;
}

void Scene::update(float dt)
{
	m_timer += dt;
	m_camera->move(m_win->getContext(), dt);
	m_proj = m_win->getPerspective();
	m_view = *m_camera->getView();
}

void Scene::render()
{
	glClearColor(0.25f, 0.35f, 0.65f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto renderable : m_renderables)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::sin(m_timer) * glm::two_pi<float>() * 0.5f, { 1.0f, 1.0f, 1.0f });
		renderable->setModel(model);

		Material mat = *renderable->getMaterial();
		mat.m_shader.use();
		mat.m_shader.setVec3("uColor", mat.m_diff);
		mat.m_shader.setMat4("uProj", m_proj);
		mat.m_shader.setMat4("uView", m_view);
		mat.m_shader.setMat4("uModel", *renderable->getModel());

		renderable->getVao()->bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		renderable->getVao()->unBind();
	}
	
	glDepthFunc(GL_LEQUAL);
	Material skyBoxMat = *m_skybox->getMaterial();
	glm::mat4 view = glm::mat4(glm::mat3(*m_camera->getView()));

	skyBoxMat.m_shader.use();
	skyBoxMat.m_shader.setMat4("uView", view);
	skyBoxMat.m_shader.setMat4("uProj", m_proj);

	m_skybox->getVao()->bind();
	glActiveTexture(GL_TEXTURE0);
	m_skybox->getCubeMap()->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}