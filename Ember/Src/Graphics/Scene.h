#pragma once
#include "Mesh.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <vector>

struct SceneSettings
{
	float m_fov;
	float m_asspect;
	float m_near;
	float m_far;
};

class Scene
{
public:
	Scene(SceneSettings settings);
	~Scene();

	void addMesh(Mesh* mesh);
	void addCamera(Camera* camera, bool mainCam);
	void update(GLFWwindow* win, float dt);
	void render();

private:
	SceneSettings m_settings;
	std::vector<Mesh*> m_meshes;
	std::vector<Camera*> m_cameras;
	Camera* m_mainCamera;
	glm::mat4 m_view;
	glm::mat4 m_proj;
};