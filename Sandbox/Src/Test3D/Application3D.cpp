#include "Application3D.h"

Application3D::Application3D(const Ember::Core::ApplicationCreateInfo& createInfo) :
	Application{ createInfo }, m_lastFrame{ 0.0f }, m_window{ nullptr }, m_scene{ nullptr }, m_renderer{ nullptr},
	m_camera{nullptr},  m_shader{nullptr}, m_gui{nullptr}, m_skyBoxShader{nullptr}
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
		float currFrame = glfwGetTime();
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

	// set our api
	windowCreateInfo.m_api = "API_OPENGL";		

	// give a width
	windowCreateInfo.m_width = 1440;	

	// give a height
	windowCreateInfo.m_height = 1080;

	// give our app a name
	windowCreateInfo.m_label = "Application 3D";

	// create our new window
	m_window = std::make_shared<Ember::Core::Window>(windowCreateInfo);
}

void Application3D::createScene()
{
	Ember::Scene::CameraCreateInfo cameraCreateInfo{};

	// pass a pointer to our window to the camera to be able to move
	cameraCreateInfo.m_winContext = *m_window->getContext();

	// where is the camera located
	cameraCreateInfo.m_pos = { 1.0f, 1.0f, 10.0f };	

	// which was is forward
	cameraCreateInfo.m_front = { -0.50f, -0.90f, 0.0f };	

	// which way is up
	cameraCreateInfo.m_worldUp = { 0.0f, 1.0f, 0.0f };	

	// rotate about y-axis
	cameraCreateInfo.m_yaw = -90.0f;			

	// rotate about x-axis
	cameraCreateInfo.m_pitch = 0.0f;		

	// how fast is the camera
	cameraCreateInfo.m_speed = 7.5f;

	// how far can we zoom
	cameraCreateInfo.m_zoom = 45.0f;

	// how sensitive is the camera
	cameraCreateInfo.m_sensitivity = 0.25f;

	// what is the near clipping plane
	cameraCreateInfo.m_near = 0.1f;

	// what is the far clipping plane
	cameraCreateInfo.m_far = 100.0f;

	// create camera
	m_camera = std::make_shared<Ember::Scene::Camera>(cameraCreateInfo);

	// create scene shader
	m_shader = std::make_shared<Ember::Renderer::Shader>(SHADER_PATH "basicShading.hlsl");

	// add our skybox shader
	m_skyBoxShader = std::make_shared<Ember::Renderer::Shader>(SHADER_PATH "skyBox.hlsl");

	Ember::Scene::SceneCreateInfo sceneCreateInfo{};

	// give our scene a camera
	sceneCreateInfo.m_camera = m_camera;	

	// give our scene a shader
	sceneCreateInfo.m_shader = m_shader;	

	// give our scene a skybox shader
	sceneCreateInfo.m_skyboxShader = m_skyBoxShader;

	// create scene
	m_scene = std::make_shared<Ember::Scene::Scene>(sceneCreateInfo);
}

void Application3D::createRenderer()
{
	Ember::Renderer::RendererCreateInfo rendererCreateInfo;

	// set a backend API
	rendererCreateInfo.m_api = "API_OPENGL";		

	// do we want a GUI
	rendererCreateInfo.m_guiEnabled = true;

	// set a background color
	rendererCreateInfo.m_backgroundCol = { 0.2f, 0.3f, 0.3f, 1.0f };

	//create a gui for our renderer to render
	Ember::Core::GuiCreateInfo guiCreateInfo{};

	// pass our window to the gui
	guiCreateInfo.m_window = m_window;

	// pass our scene to the gui to be able to manipulate it
	guiCreateInfo.m_scene = m_scene;
	m_gui = std::make_shared<ImguiGui>(guiCreateInfo);

	// add the gui to our renderer
	rendererCreateInfo.m_gui = m_gui;

	// give our renderer a scene to render
	rendererCreateInfo.m_scene = m_scene;

	// give our renderer a window to render to
	rendererCreateInfo.m_window = m_window;		

	// do we want a skybox
	rendererCreateInfo.m_skyBoxEnabled = true;

	// need to give skybox files
	rendererCreateInfo.m_skyBoxFiles = {
		TEXTURE_PATH "skybox/right.jpg",
		TEXTURE_PATH "skybox/left.jpg",
		TEXTURE_PATH "skybox/top.jpg" ,
		TEXTURE_PATH "skybox/bottom.jpg" ,
		TEXTURE_PATH "skybox/front.jpg" ,
		TEXTURE_PATH "skybox/back.jpg" 
	};

	// create our renderer
	m_renderer = std::make_shared<Ember::Renderer::Renderer>(rendererCreateInfo);
}

void Application3D::addSceneObjects()
{
	// add two trees to the scene
	int32_t numTrees{ 2 };
	glm::vec3 pos{ -2.5f, 0.0f, 0.0f };
	for (int32_t i{ 0 }; i < numTrees; i++)
	{
		Ember::Scene::EntityCreateInfo createInfo{};
		createInfo.m_name = "Tree" + std::to_string(i);
		createInfo.m_objFile = OBJ_PATH "tree/tree.obj";
		
		// give path, not file
		createInfo.m_mtlFile = OBJ_PATH "tree/";
		createInfo.m_type = Ember::Scene::EntityType::RENDERABLE;
		createInfo.m_position = pos;

		m_scene->addEntity(EMBER_NEW Ember::Scene::Entity(createInfo));

		pos.x += 5.0f;
	}

	// add skybox to the scene
	Ember::Scene::EntityCreateInfo createInfo{};
	createInfo.m_name = "Skybox";
	createInfo.m_type = Ember::Scene::EntityType::SKYBOX;
	createInfo.m_objFile = OBJ_PATH "skybox/skybox.obj";
	createInfo.m_mtlFile = "";
	m_scene->addSkybox(EMBER_NEW Ember::Scene::Entity(createInfo));	
}

void Application3D::onStart()
{
	// create window first
	createWindow();			

	// then the scene
	createScene();

	// add some objects to the scene
	addSceneObjects();

	// create our renderer once the scene has been populated
	createRenderer();		
}

void Application3D::onUpdate(float dt)
{
	// update things in our scene
	m_renderer->update(dt);
}

void Application3D::onRender()
{
	// render our scene 
	m_renderer->render();
}