#pragma once
#include "Mesh.h"
#include "LightCaster.h"
#include "Camera.h"
#include "../Core/Window.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct SceneSettings
{
	Window* m_window;
};

class Scene
{
public:
	Scene(SceneSettings settings);
	~Scene();

	void addMesh(Mesh* mesh);
	void addDirLightCaster(LightCaster<DirectionalLight>* light);
	void addCamera(Camera* camera, bool mainCam);
	void update(float dt);
	glm::mat4* getView(void);
	glm::mat4* getProj(void);
	std::vector<Mesh*>* getMeshes(void);
	LightCaster<DirectionalLight>* getDirLightCaster(void);
	Mesh* getSkybox(void);
	Camera* getMainCam(void);

private:
	SceneSettings m_settings;
	Camera* m_mainCamera;
	Mesh* m_skybox;
	std::vector<Mesh*> m_meshes;
	LightCaster<DirectionalLight>* m_dirLightCaster;
	std::vector<Camera*> m_cameras;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	const uint32_t c_maxLights = 50;
};