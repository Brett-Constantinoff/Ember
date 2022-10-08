#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : Layer(name)
{
}

Test3DLayer::~Test3DLayer()
{
	delete m_shader;
	delete m_vbo;
	delete m_vao;
}

void Test3DLayer::onAttach(Window* win)
{
	m_win = win;
	m_shader = new Shader("../../Src/Test3D/Assets/Hlsl/basicShader.hlsl");

	m_vao = new VertexArray();
	m_vao->bind();

	float vertexPos[] = {
		-0.5f, -0.5f, 0.0f, 
		0.0f, 0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f
	};
	m_vbo = new VertexBuffer(GL_ARRAY_BUFFER);
	m_vbo->bind();
	m_vbo->setData(sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	m_vao->setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}

void Test3DLayer::onDetach(void)
{

}

void Test3DLayer::onUpdate(float dt)
{

}

void Test3DLayer::onRender(void)
{
	glClearColor(0.25f, 0.35f, 0.65f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_vao->bind();
	m_shader->use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Test3DLayer::onImguiRender(void)
{

}