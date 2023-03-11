#include "Application3D.h"

Application3D::Application3D(const Ember::Core::ApplicationCreateInfo& createInfo) :
	Application{ createInfo }, m_lastFrame{ 0.0f }, m_window{ nullptr }, m_scene{ nullptr }, m_renderer{ nullptr},
	m_camera{nullptr},  m_shader{nullptr}, m_gui{nullptr}
{
}

Application3D::~Application3D()
{
	// cleanup memory used by the application
	EMBER_DELETE m_window;
	EMBER_DELETE m_renderer;
	EMBER_DELETE m_camera;
	EMBER_DELETE m_shader;
	EMBER_DELETE m_scene;
	EMBER_DELETE m_gui;
}

void Application3D::run()
{
	// setup app
	onStart();	

	// main application loop
	while (m_window->isOpen())
	{
		double currFrame = glfwGetTime();										
		double dt = currFrame - m_lastFrame;									
		m_lastFrame = currFrame;												

		onUpdate(dt);															
		onRender();																

		m_window->update();														
	}
}

void Application3D::createWindow()
{
	Ember::Core::WindowCreateInfo windowCreateInfo{};

	// set our api
	windowCreateInfo.m_api = "API_OPENGL";		

	// give a width
	windowCreateInfo.m_width = 1440;	

	// give a height
	windowCreateInfo.m_height = 1080;

	// give our app a name
	windowCreateInfo.m_label = "Application 3D";

	// these next 3 are for perspective viwing
	windowCreateInfo.m_fov = 90.0f;												
	windowCreateInfo.m_near = 0.1f;												
	windowCreateInfo.m_far = 100.0f;		

	// create our new window
	m_window = EMBER_NEW Ember::Core::Window(windowCreateInfo);					
}

void Application3D::createScene()
{
	Ember::Scene::CameraCreateInfo cameraCreateInfo{};

	// where is the camera located
	cameraCreateInfo.m_pos = { 0.0f, 0.0f, 5.0f };	

	// which was is forward
	cameraCreateInfo.m_front = { 0.0f, 0.0f, -1.0f };	

	// which way is up
	cameraCreateInfo.m_up = { 0.0f, 1.0f, 0.0f };	

	// rotate about y-axis
	cameraCreateInfo.m_yaw = -90.0f;			

	// rotate about x-axis
	cameraCreateInfo.m_pitch = 0.0f;		

	// create camera
	m_camera = EMBER_NEW Ember::Scene::Camera(cameraCreateInfo);				

	// create scene shader
	m_shader = EMBER_NEW Ember::Renderer::Shader(SHADER_PATH "flatShading.hlsl");

	Ember::Scene::SceneCreateInfo sceneCreateInfo{};

	// give our scene a camera
	sceneCreateInfo.m_camera = m_camera;	

	// give our scene a shader
	sceneCreateInfo.m_shader = m_shader;	

	// pass a pointer to our window
	sceneCreateInfo.m_windowContext = *m_window->getContext();	

	// create scene
	m_scene = EMBER_NEW Ember::Scene::Scene(sceneCreateInfo);					
}

void Application3D::createRenderer()
{
	Ember::Renderer::RendererCreateInfo rendererCreateInfo;

	// set a backend API
	rendererCreateInfo.m_api = "API_OPENGL";		

	// do we want a GUI
	rendererCreateInfo.m_guiEnabled = true;			

	//create a gui for our renderer to render
	Ember::Core::GuiCreateInfo guiCreateInfo{};

	// pass our window to the gui
	guiCreateInfo.m_window = m_window;

	// pass our scene to the gui to be able to manipulate it
	guiCreateInfo.m_scene = m_scene;
	m_gui = EMBER_NEW ImguiGui(guiCreateInfo);

	// add the gui to our renderer
	rendererCreateInfo.m_gui = m_gui;

	// give our renderer a scene to render
	rendererCreateInfo.m_scene = m_scene;

	// give our renderer a window to render to
	rendererCreateInfo.m_window = m_window;		

	// create our renderer
	m_renderer = EMBER_NEW Ember::Renderer::Renderer(rendererCreateInfo);		
}

void Application3D::onStart()
{
	// initial app creation
	createWindow();																
	createScene();																
	createRenderer();															
}

void Application3D::onUpdate(double dt)
{
	// update things in our scene
	m_renderer->update(dt);
}

void Application3D::onRender()
{
	// render our scene 
	m_renderer->render();
}