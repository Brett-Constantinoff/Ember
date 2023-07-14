#include "Application3D.h"

Application3D::Application3D(const Ember::Core::ApplicationCreateInfo& createInfo) :
	Application{ createInfo }, m_lastFrame{ 0.0f }, m_window{ nullptr }, m_scene{ nullptr }, m_renderer{ nullptr},
	m_camera{nullptr}, m_gui{nullptr}
{
}

Application3D::~Application3D()
{

}

void Application3D::run()
{
	// setup app
	onStart();	

	// main application loop
	while (m_window->isOpen())
	{
		float currFrame = static_cast<float>(glfwGetTime());
		float dt = currFrame - m_lastFrame;
		m_lastFrame = currFrame;												

		onUpdate(dt);															
		onRender();																

		m_window->update();														
	}
}

void Application3D::createWindow()
{
	Ember::Core::WindowCreateInfo windowCreateInfo{};
	windowCreateInfo.m_api = Ember::Core::WindowApi::Vulkan;		
	windowCreateInfo.m_width = 500;	
	windowCreateInfo.m_height = 500;
	windowCreateInfo.m_label = "Application 3D";
	m_window = std::make_shared<Ember::Core::Window>(windowCreateInfo);
}

void Application3D::createScene()
{
	Ember::Scene::CameraCreateInfo cameraCreateInfo{};

	cameraCreateInfo.m_winContext = *m_window->getContext();
	cameraCreateInfo.m_pos = { 1.0f, 1.0f, 10.0f };	
	cameraCreateInfo.m_front = { -0.50f, -0.90f, 0.0f };	
	cameraCreateInfo.m_worldUp = { 0.0f, 1.0f, 0.0f };	
	cameraCreateInfo.m_yaw = -90.0f;			
	cameraCreateInfo.m_pitch = 0.0f;		
	cameraCreateInfo.m_speed = 7.5f;
	cameraCreateInfo.m_zoom = 45.0f;
	cameraCreateInfo.m_sensitivity = 0.25f;
	cameraCreateInfo.m_near = 0.1f;
	cameraCreateInfo.m_far = 100.0f;
	m_camera = std::make_shared<Ember::Scene::Camera>(cameraCreateInfo);

	Ember::Scene::SceneCreateInfo sceneCreateInfo{};
	sceneCreateInfo.m_camera = m_camera;	
	sceneCreateInfo.m_sceneShading = Ember::Scene::SceneShading::Basic;
	sceneCreateInfo.m_customShader = nullptr;
	sceneCreateInfo.m_enableSkybox = false;
	m_scene = std::make_shared<Ember::Scene::Scene>(sceneCreateInfo);
}

void Application3D::createRenderer()
{
	Ember::Renderer::RendererCreateInfo rendererCreateInfo;
	
	rendererCreateInfo.m_guiEnabled = false;
	rendererCreateInfo.m_backgroundCol = { 0.2f, 0.3f, 0.3f, 1.0f };
	Ember::Core::GuiCreateInfo guiCreateInfo{};
	guiCreateInfo.m_window = m_window;
	guiCreateInfo.m_scene = m_scene;
	//m_gui = std::make_shared<ImguiGui>(guiCreateInfo);
	rendererCreateInfo.m_gui = m_gui;
	rendererCreateInfo.m_scene = m_scene;
	rendererCreateInfo.m_window = m_window;		
	m_renderer = std::make_shared<Ember::Renderer::Renderer>(rendererCreateInfo);
}

void Application3D::addSceneObjects()
{
	// add some objects to the scene
	Ember::Scene::EntityCreateInfo createInfo{};

	createInfo.m_name = "sponza";
	createInfo.m_objFile = OBJ_PATH "sponza/sponza.obj";
	createInfo.m_mtlFile = OBJ_PATH "sponza/";
	createInfo.m_type = Ember::Scene::EntityType::Renderable;
	//m_scene->addEntity(EMBER_NEW Ember::Scene::Entity(createInfo));
}

void Application3D::onStart()
{
	createWindow();			
	createScene();
	addSceneObjects();
	createRenderer();		
}

void Application3D::onUpdate(float dt)
{
	m_renderer->update(dt);
}

void Application3D::onRender()
{
	m_renderer->render();
}