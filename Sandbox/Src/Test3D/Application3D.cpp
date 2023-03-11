#include "Application3D.h"

Application3D::Application3D(const Ember::Core::ApplicationCreateInfo& createInfo) :
	Application{ createInfo }, m_lastFrame{ 0.0f }, m_window{ nullptr }, m_scene{ nullptr }, m_renderer{ nullptr},
	m_camera{nullptr},  m_shader{nullptr}
{
}

Application3D::~Application3D()
{
	// cleanup memory used by the application
	delete m_window;
	delete m_renderer;
	delete m_camera;
	delete m_shader;
	delete m_scene;
}

void Application3D::run()
{
	onStart();																	// do any intial setup
	while (m_window->isOpen())
	{
		double currFrame = glfwGetTime();										// get current time
		double dt = currFrame - m_lastFrame;									// calculate change in time (tick speed)
		m_lastFrame = currFrame;												// update the last frame time

		onUpdate(dt);															// update the application
		onRender();																// render anything to the screen

		m_window->update();														// update our window
	}
}

void Application3D::createWindow()
{
	Ember::Core::WindowCreateInfo windowCreateInfo;							
	windowCreateInfo.m_api = "API_OPENGL";										// api version
	windowCreateInfo.m_width = 1080;											// window width
	windowCreateInfo.m_height = 1080;											// window height
	windowCreateInfo.m_label = "Application 3D";								// give out app a label
	windowCreateInfo.m_fov = 90.0f;												// set a FOV, for 3D perspective viewing
	windowCreateInfo.m_near = 0.1f;												// set near plane
	windowCreateInfo.m_far = 100.0f;											// set far plane
	m_window = EMBER_NEW Ember::Core::Window(windowCreateInfo);					// create our new window
}

void Application3D::createScene()
{
	Ember::Scene::CameraCreateInfo cameraCreateInfo;
	cameraCreateInfo.m_pos = { 0.0f, 0.0f, 5.0f };								// camera starting position
	cameraCreateInfo.m_front = { 0.0f, 0.0f, -1.0f };							// camera front vector (which way itll point)
	cameraCreateInfo.m_up = { 0.0f, 1.0f, 0.0f };								// which way is up
	cameraCreateInfo.m_yaw = -90.0f;											// side to side rotation
	cameraCreateInfo.m_pitch = 0.0f;											// up down rotation
	m_camera = EMBER_NEW Ember::Scene::Camera(cameraCreateInfo);				// create scene camera

	m_shader = EMBER_NEW Ember::Renderer::Shader(SHADER_PATH "flatShading.hlsl");// create scene shader

	Ember::Scene::SceneCreateInfo sceneCreateInfo;						
	sceneCreateInfo.m_camera = m_camera;										// pass our camera to the scene
	sceneCreateInfo.m_shader = m_shader;										// pass shader to the scene
	sceneCreateInfo.m_windowContext = *m_window->getContext();					// pass our window context to the scene
	m_scene = EMBER_NEW Ember::Scene::Scene(sceneCreateInfo);					// create our scene
}

void Application3D::createRenderer()
{
	Ember::Renderer::RendererCreateInfo rendererCreateInfo;
	rendererCreateInfo.m_api = "API_OPENGL";									// api version (only one for now)
	rendererCreateInfo.m_imguiEnabled = true;									// do we want GUI
	rendererCreateInfo.m_scene = m_scene;										// pass our scene to the renderer
	rendererCreateInfo.m_window = m_window;										// pass a pointer to our window
	m_renderer = EMBER_NEW Ember::Renderer::Renderer(rendererCreateInfo);		// create our new renderer
}

void Application3D::onStart()
{
	createWindow();																// create window
	createScene();																// create scene
	createRenderer();															// create renderer
}

void Application3D::onUpdate(double dt)
{
	m_renderer->update(dt);
}

void Application3D::onRender()
{
	m_renderer->render();
}