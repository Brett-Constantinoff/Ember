#include "Application3D.h"
#include "FastNoiseLite.h"

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

	Ember::Scene::SceneCreateInfo sceneCreateInfo{};

	// give our scene a camera
	sceneCreateInfo.m_camera = m_camera;	

	// set our shading type
	sceneCreateInfo.m_sceneShading = Ember::Scene::SceneShading::BASIC;

	// dont want custom shading
	sceneCreateInfo.m_customShader = nullptr;

	// enable a skybox
	sceneCreateInfo.m_enableSkybox = true;

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

	// create our renderer
	m_renderer = std::make_shared<Ember::Renderer::Renderer>(rendererCreateInfo);
}

void Application3D::addSceneObjects()
{
	/*
	// add some objects to the scene
	Ember::Scene::EntityCreateInfo createInfo{};

	createInfo.m_name = "sponza";
	createInfo.m_objFile = OBJ_PATH "sponza/sponza.obj";
	createInfo.m_mtlFile = OBJ_PATH "sponza/";
	createInfo.m_type = Ember::Scene::EntityType::RENDERABLE;
	m_scene->addEntity(EMBER_NEW Ember::Scene::Entity(createInfo));
	*/
	
	Ember::Scene::EntityCreateInfo createInfo{};
	createInfo.m_name = "Custom Entity";
	createInfo.m_type = Ember::Scene::EntityType::CUSTOM;
	/*createInfo.m_vertexPositions = {
		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		-0.5f,  0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f, -0.5f,  
		 0.5f, -0.5f,  0.5f,  
		 0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f, -0.5f,  
		-0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f, -0.5f,  
		 0.5f,  0.5f,  0.5f,  
		 0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,  	
	};*/

	//generate verticies for a plane
	int32_t m_width = 10; //width of plane
	int32_t m_height = 10; //height of plane
	int32_t m_quads = (m_width < m_height) ? m_width/2 : m_height/2; //number of quads in plane

	std::vector<std::vector<float>> heightMap = createNoiseMap(m_width, m_height, 100, 4, 0.5, 2);

	//print the noiseMap
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			std::cout << heightMap[y][x] << " ";
		}
		std::cout << std::endl;
	}
	
	m_scene->addEntity(EMBER_NEW Ember::Scene::Entity(createInfo));
}

std::vector<std::vector<float>> createNoiseMap(int32_t width, int32_t height, float scale, int32_t octaves, float persistence, float lacunarity)
{

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	std::vector<std::vector<float>> noiseMap;
	
	if (scale <= 0)
	{
		scale = (float)0.001;
	}

	for (int32_t y = 0; y < height; y++)
	{
		std::vector<float> row;
		for (int32_t x = 0; x < width; x++)
		{
			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;
			for (int32_t i = 0; i < octaves; i++)
			{
				float sampleX = x / scale * frequency;
				float sampleY = y / scale * frequency;
				float perlinValue = noise.GetNoise(sampleX, sampleY);
				noiseHeight += perlinValue * amplitude;
				amplitude *= persistence;
				frequency *= 2;
			}
			row.push_back(noiseHeight);
		}
		noiseMap.push_back(row);
	}

	return noiseMap;
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