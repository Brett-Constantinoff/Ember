#include "Scene.h"

Scene::Scene() :
	m_camera{nullptr}, m_skybox{nullptr}, m_dirLight{nullptr},
	m_win{nullptr}, m_proj{glm::mat4(1.0f)}, m_view{glm::mat4(1.0f)},
	m_shadowFbo{GL_FRAMEBUFFER}, m_depthTex{GL_TEXTURE_2D, 1024, 1024}
{
	glEnable(GL_DEPTH_TEST);
	m_shadowFbo.attachDepthTex(m_depthTex);
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
	delete m_dirLight;
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

void Scene::addDirLight(DirectionalLight* light)
{
	m_dirLight = light;
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
	
	renderNormalScene();
}

void Scene::renderNormalScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto renderable : m_renderables)
	{
		renderObj(renderable);
	}
	renderSkybox();
}

void Scene::renderObj(SceneObject* obj)
{
	Transformation trans = *obj->getTransform();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, trans.m_translation);
	model *= trans.m_rotation;
	model = glm::scale(model, trans.m_scale);

	Material mat = *obj->getMaterial();
	mat.m_shader.use();
	mat.m_shader.setVec3("uDiff", mat.m_diff);
	mat.m_shader.setMat4("uProj", m_proj);
	mat.m_shader.setMat4("uView", m_view);
	mat.m_shader.setMat4("uModel", model);

	if (mat.m_lit)
	{
		mat.m_shader.setVec3("uAmb", mat.m_amb);
		mat.m_shader.setVec3("uSpec", mat.m_spec);
		mat.m_shader.setFloat("uShine", mat.m_shine);

		mat.m_shader.setVec3("uDirLight.m_dir", m_dirLight->m_dir);
		mat.m_shader.setVec3("uDirLight.m_diff", m_dirLight->m_diff);
		mat.m_shader.setVec3("uDirLight.m_amb", m_dirLight->m_amb);
		mat.m_shader.setVec3("uDirLight.m_spec", m_dirLight->m_spec);

		mat.m_shader.setVec3("uViewPos", *m_camera->getPos());
	}

	obj->getVao()->bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	obj->getVao()->unBind();
}

void Scene::renderSkybox()
{
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

