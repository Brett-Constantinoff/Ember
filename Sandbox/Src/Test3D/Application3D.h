#pragma once
#include <Engine.h>

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

	virtual void onStart();
	virtual void onUpdate(double dt);
	virtual void onRender();

private:
	double m_lastFrame;
	Ember::Core::Window* m_window;
	Ember::Scene::Scene* m_scene;
	Ember::Renderer::Renderer* m_renderer;
	Ember::Scene::Camera* m_camera;
	Ember::Renderer::Shader* m_shader;
};