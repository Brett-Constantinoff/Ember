#pragma once
#include "../Renderer/Camera.h"
#include "../Core/Window.h"
#include "SkyBox.h"
#include "SceneObject.h"
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
	std::vector<SceneObject*>* getRenderables();
	void update(float dt);
	void render();
	
private:
	std::vector<SceneObject*> m_renderables;
	Camera* m_camera = nullptr;
	Window* m_win = nullptr;
	SkyBox* m_skybox = nullptr;
	glm::mat4 m_proj{};
	glm::mat4 m_view{};
	float m_timer = 0.0f;
};