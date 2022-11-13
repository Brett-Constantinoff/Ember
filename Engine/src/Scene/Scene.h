#pragma once
#include "../Renderer/Camera.h"
#include "../Renderer/Framebuffer.h"
#include "../Renderer/Texture2D.h"
#include "../Core/Window.h"
#include "SkyBox.h"
#include "SceneObject.h"
#include "DirectionalLight.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	void addRenderable(SceneObject* obj);
	void addCamera(Camera* camera);
	void addContext(Window* win);
	void addSkyBox(SkyBox* skybox);
	void addDirLight(DirectionalLight* light);
	void update(float dt);
	void render();

private:
	void renderNormalScene();
	void renderObj(SceneObject* obj);
	void renderSkybox();
	
private:
	std::vector<SceneObject*> m_renderables;
	Camera* m_camera;
	Window* m_win;
	SkyBox* m_skybox;
	DirectionalLight* m_dirLight;
	Framebuffer m_shadowFbo;
	Texture2D m_depthTex;
	glm::mat4 m_proj;
	glm::mat4 m_view;
};