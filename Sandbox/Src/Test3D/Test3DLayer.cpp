#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : Layer(name)
{
}

Test3DLayer::~Test3DLayer()
{
	delete m_vb;
}

void Test3DLayer::onAttach(Window* win)
{
	m_win = win;

	m_vb = new VertexBuffer(GL_ARRAY_BUFFER);
}

void Test3DLayer::onDetach(void)
{

}

void Test3DLayer::onUpdate(float dt)
{

}

void Test3DLayer::onRender(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Test3DLayer::onImguiRender(void)
{
	//debug
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
}