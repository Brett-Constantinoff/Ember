#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : 
    Layer(name), m_shader{ SHADER_PATH "basicShader.hlsl" }, m_camera{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
    m_vbo{ GL_ARRAY_BUFFER }, m_colorBuffer{ GL_ARRAY_BUFFER }, m_vao{}, m_win{nullptr}, m_proj{glm::mat4(1.0f)}, m_cubeModel{glm::mat4(1.0f)}, m_timer{0.0f}
{
}

Test3DLayer::~Test3DLayer()
{
}

void Test3DLayer::onAttach(Window* win)
{
    glEnable(GL_DEPTH_TEST);

	m_win = win;

	m_vao.bind();

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
	m_vbo.bind();
	m_vbo.setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

    m_colorBuffer.bind();
    m_colorBuffer.setData(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    m_vao.setLayout(3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
}

void Test3DLayer::onDetach(void)
{

}

void Test3DLayer::onUpdate(float dt)
{
    m_timer += dt;

    glClearColor(0.25f, 0.35f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_camera.move(m_win->getContext(), dt);
    m_proj = glm::perspective(glm::radians(45.0f), static_cast<float>(m_win->getWidth()) / static_cast<float>(m_win->getHeight()), 0.1f, 100.0f);
    m_cubeModel = glm::mat4(1.0f);
    m_cubeModel = glm::rotate(m_cubeModel, glm::sin(m_timer) * glm::two_pi<float>() * 0.5f, { 1.0f, 1.0f, 1.0f });

    m_shader.use();
    m_shader.setMat4("uProj", m_proj);
    m_shader.setMat4("uView", *m_camera.getView());
    m_shader.setMat4("uModel", m_cubeModel);
    m_vao.bind();
}

void Test3DLayer::onRender(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Test3DLayer::onImguiRender(void)
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}