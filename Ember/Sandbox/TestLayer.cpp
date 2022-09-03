#include "TestLayer.h"

TestLayer::TestLayer()
{
}

TestLayer::~TestLayer()
{
	delete m_renderer;
	delete m_scene;
}

void TestLayer::onAttach(Window* win)
{
	m_win = win;

	//renderer setup
	RenderSettings renderSettings{
		false,
	};
	m_renderer = new Renderer(renderSettings);

	//scene setup
	SceneSettings sceneSettings = {
		m_win,
	};
	m_scene = new Scene(sceneSettings);

	//make this camera the main scene camera
	m_scene->addCamera(new Camera(CameraProps{ { 0.0f, 5.0f, 15.0f } }), true);

	//add some primitives
	const char* phongNoText = ".\\Src\\Shaders\\phongNoText.hlsl";
	const char* phongText = ".\\Src\\Shaders\\phongShader.hlsl";
	
	Geometry quadGeo(Primitive::QUAD);
	//bronze
	Material quadMat = { MaterialProps{phongNoText, nullptr, {0.22f, 0.13f, 0.05f}, {0.71f, 0.43f, 0.18f}, {0.39f, 0.27f, 0.17f}, 128.0f * 0.2f } };
	Mesh* quad = new Mesh(quadGeo, quadMat);
	quad->scale({ 20.0f, 20.0f, 20.0f });
	m_scene->addMesh(quad);
	
	Geometry cubeGeo(Primitive::CUBE);
	//emerald
	Material cubeMat = { MaterialProps{phongNoText, nullptr, {0.02f, 0.17f, 0.02f}, {0.08f, 0.61f, 0.08f}, {0.63f, 0.73f, 0.64f}, 128.0f * 0.6 }};
	Mesh* cube = new Mesh(cubeGeo, cubeMat);
	cube->translate({ 2.0f, 0.5f, 0.0f });
	m_scene->addMesh(cube);
	

	Geometry cube2Geo(Primitive::CUBE);
	//chrome
	Material cube2Mat = { MaterialProps{phongNoText, nullptr, {0.25f, 0.25f, 0.25f}, {0.4f, 0.4f, 0.4f}, {0.77f, 0.77f, 0.77f}, 128.0f * 0.6} };
	Mesh* cube2 = new Mesh(cube2Geo, cube2Mat);
	cube2->translate({ -2.0f, 1.0f, 0.0f });
	cube2->scale({ 2.0f, 2.0f, 2.0f });
	m_scene->addMesh(cube2);
	
	
	for (int32_t i = 0; i < 10; i++)
	{
		Geometry spherGeo(Primitive::SPHERE);
		//pearl
		Material sphereMat = { MaterialProps{phongNoText, nullptr, {0.25f, 0.21f, 0.21f}, {1.0f, 0.83f, 0.83f}, {0.30f, 0.30f, 0.30f}, 128.0f * 0.09f} };
		Mesh* sphere = new Mesh(spherGeo, sphereMat);
		sphere->scale({ 0.5f, 0.5f, 0.5f });
		sphere->translate({ -5.0f, 0.5f, (i - 5.0f) * 2.0f});
		m_scene->addMesh(sphere);
	}
	
	LightColor color = { {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
	LightCaster<DirectionalLight>* dirLightCaster = new LightCaster<DirectionalLight>( DirectionalLight{color, {0.0f, -1.0f, 0.0f}} );
	m_scene->addDirLightCaster(dirLightCaster);
}

void TestLayer::onDetach()
{
}

void TestLayer::onUpdate(float dt)
{
	//update everything in the scene
	m_scene->update(dt);
}

void TestLayer::onRender()
{
	//render everything in the scene
	m_renderer->render(m_scene);
}

void TestLayer::onImguiRender()
{
	//debug
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
}
