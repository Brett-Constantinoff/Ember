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

	RenderSettings renderSettings{
		m_win,
		false,
	};
	m_renderer = new Renderer(renderSettings);
	m_renderer->enableSkybox();

	SceneSettings sceneSettings = {
		glm::radians(45.0f),
		static_cast<float>(m_win->getWidth()) / static_cast<float>(m_win->getHeight()),
		0.01f,
		100.0f
	};
	m_scene = new Scene(sceneSettings);
	m_scene->addCamera(new Camera({ 0.0f, 5.0f, 15.0f }), true);

	m_scene->addSkybox({
		".\\Src\\Assets\\Textures\\MountainSkybox\\right.jpg",
		".\\Src\\Assets\\Textures\\MountainSkybox\\left.jpg",
		".\\Src\\Assets\\Textures\\MountainSkybox\\top.jpg",
		".\\Src\\Assets\\Textures\\MountainSkybox\\bottom.jpg",
		".\\Src\\Assets\\Textures\\MountainSkybox\\front.jpg",
		".\\Src\\Assets\\Textures\\MountainSkybox\\back.jpg",
	});
	
	
	Geometry quadGeo(Type::QUAD);
	Material quadMat = { ".\\Src\\Shaders\\basicShader.hlsl", nullptr, {0.56f ,0.23f, 0.85f} };
	Mesh* quad = new Mesh(quadGeo, quadMat);
	quad->translate({ 0.0f, -2.0f, 0.0f });
	quad->scale({ 20.0f, 20.0f, 20.0f });
	quad->rotate(90.0f, { 1.0f, 0.0f, 0.0f });
	m_scene->addMesh(quad);
	
	Geometry cubeGeo(Type::CUBE);
	Material cubeMat = { ".\\Src\\Shaders\\basicShader.hlsl", ".\\Src\\Assets\\Textures\\woodenBox.jpg"};
	Mesh* cube = new Mesh(cubeGeo, cubeMat);
	cube->translate({ 2.0f, 0.0f, 0.0f });
	m_scene->addMesh(cube);

	Geometry cube2Geo(Type::CUBE);
	Material cube2Mat = { ".\\Src\\Shaders\\basicShader.hlsl", ".\\Src\\Assets\\Textures\\woodenBox.jpg", {0.53f, 0.68f, 0.12f} };
	Mesh* cube2 = new Mesh(cube2Geo, cube2Mat);
	cube2->translate({ -2.0f, 0.0f, 0.0f });
	cube2->scale({ 2.0f, 2.0f, 2.0f });
	m_scene->addMesh(cube2);
	
	Geometry spherGeo = { Type::SPHERE };
	Material sphereMat = { ".\\Src\\Shaders\\basicShader.hlsl", ".\\Src\\Assets\\Textures\\brick.jpg" };
	Mesh* sphere = new Mesh(spherGeo, sphereMat);
	sphere->translate({ -5.5f, 3.0f, 6.0f });
	m_scene->addMesh(sphere);
	

	Geometry cylGeo = { Type::CYLINDER };
	Material cylMat = { ".\\Src\\Shaders\\basicShader.hlsl", nullptr, {0.14f, 0.28f, 0.36f} };
	Mesh* cyl = new Mesh(cylGeo, cylMat);
	cyl->translate({ 1.5f, 0.0f, -3.5f });
	m_scene->addMesh(cyl);
}

void TestLayer::onDetach()
{
}

void TestLayer::onUpdate(float dt)
{
	m_scene->update(*m_win->getContext(), dt);
}

void TestLayer::onRender()
{
	m_renderer->render(m_scene);
}

void TestLayer::onImguiRender()
{
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
}
