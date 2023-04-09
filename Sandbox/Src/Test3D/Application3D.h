#pragma once
#include <Engine.h>
#include "ImguiGui.h"


class Application3D : public Ember::Core::Application
{
public:
	Application3D(const Ember::Core::ApplicationCreateInfo& createInfo);
	~Application3D();

	virtual void run();
	
private:
	void createWindow();
	void createScene();
	void createRenderer();
	void addSceneObjects();
	//returns a 2d vector of floats between 0 and 1
	std::vector<std::vector<float>> createNoiseMap(int32_t width, int32_t height, float scale, int32_t octaves, float persistence, float lacunarity);

	virtual void onStart();
	virtual void onUpdate(float dt);
	virtual void onRender();

private:
	float m_lastFrame;
	std::shared_ptr<Ember::Core::Window> m_window;
	std::shared_ptr<Ember::Scene::Scene> m_scene;
	std::shared_ptr<ImguiGui> m_gui;
	std::shared_ptr<Ember::Renderer::Renderer> m_renderer;
	std::shared_ptr<Ember::Scene::Camera> m_camera;
};