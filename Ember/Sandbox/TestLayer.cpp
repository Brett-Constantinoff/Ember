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
		true,
	};
	m_renderer = new Renderer(renderSettings);

	SceneSettings sceneSettings = {
		glm::radians(45.0f),
		static_cast<float>(m_win->getWidth()) / static_cast<float>(m_win->getHeight()),
		0.01f,
		100.0f
	};
	m_scene = new Scene(sceneSettings);
	m_scene->addCamera(new Camera({ 0.0f, 0.0f, 7.5f }), true);

	Geometry quadGeo(Primitive::QUAD);
	Material quadMat = { ".\\Src\\Shaders\\basicShader.hlsl", glm::vec3(0.32f, 0.41f, 0.86f)};
	static Mesh quad(quadGeo, quadMat);
	quad.translate({ 0.0f, -2.0f, 0.0f });
	quad.scale({ 10.0f, 10.0f, 10.0f });
	quad.rotate(90.0f, { 1.0f, 0.0f, 0.0f });
	m_scene->addMesh(&quad);

	Geometry cubeGeo(Primitive::CUBE);
	Material cubeMat = { ".\\Src\\Shaders\\basicShader.hlsl", glm::vec3(0.75f, 0.34f, 0.23f)};
	static Mesh cube(cubeGeo, cubeMat);
	cube.translate({ 2.0f, 0.0f, 0.0f });
	m_scene->addMesh(&cube);
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
