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

void Scene::update(float dt)
{
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
		Transformation trans = *renderable->getTransform();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, trans.m_translation);
		model *= trans.m_rotation;
		model = glm::scale(model, trans.m_scale);

		Material mat = *renderable->getMaterial();
		mat.m_shader.use();
		mat.m_shader.setVec3("uColor", mat.m_diff);
		mat.m_shader.setMat4("uProj", m_proj);
		mat.m_shader.setMat4("uView", m_view);
		mat.m_shader.setMat4("uModel", model);

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