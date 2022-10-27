#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : Layer(name)
{
}

Test3DLayer::~Test3DLayer()
{
	delete m_shader;
    delete m_camera;
	delete m_vbo;
    delete m_colorBuffer;
	delete m_vao;
}

void Test3DLayer::onAttach(Window* win)
{
    glEnable(GL_DEPTH_TEST);

	m_win = win;
	m_shader = new Shader(SHADER_PATH "basicShader.hlsl");

	m_vao = new VertexArray();
	m_vao->bind();

    float vertexData[] = {
        // positions            // colors
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 
        0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 
       -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 
       -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f, 

       -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f, 
       -0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f, 
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f, 
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f, 
       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f, 
       -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, 1.0f, 

        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 1.0f,
    };
	m_vbo = new VertexBuffer(GL_ARRAY_BUFFER);
	m_vbo->bind();
	m_vbo->setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	m_vao->setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

    m_colorBuffer = new VertexBuffer(GL_ARRAY_BUFFER);
    m_colorBuffer->bind();
    m_colorBuffer->setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    m_vao->setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

    m_camera = new Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f });
    m_timer = 0.0f;
}

void Test3DLayer::onDetach(void)
{

}

void Test3DLayer::onUpdate(float dt)
{
    m_timer += dt;

    glClearColor(0.25f, 0.35f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_proj = glm::perspective(glm::radians(45.0f), static_cast<float>(m_win->getWidth()) / static_cast<float>(m_win->getHeight()), 0.1f, 100.0f);
    m_cubeModel = glm::mat4(1.0f);
    m_cubeModel = glm::rotate(m_cubeModel, glm::sin(m_timer) * glm::two_pi<float>() * 0.5f, { 1.0f, 1.0f, 1.0f });


    m_shader->use();
    m_shader->setMat4("uProj", m_proj);
    m_shader->setMat4("uView", *m_camera->getView());
    m_shader->setMat4("uModel", m_cubeModel);
    m_vao->bind();
}

void Test3DLayer::onRender(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Test3DLayer::onImguiRender(void)
{

}