#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : 
    Layer(name), m_camera{ { 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
    m_cube{nullptr}, m_win{nullptr}, m_proj{glm::mat4(1.0f)}, m_timer{0.0f}
{
    std::vector<const char*> files = {};
    m_cubeMap = new TextureCubeMap(GL_TEXTURE_CUBE_MAP, files);
}

Test3DLayer::~Test3DLayer()
{
    delete m_cubeMap;
}

void Test3DLayer::onAttach(Window* win)
{
    glEnable(GL_DEPTH_TEST);

	m_win = win;

    Material cubeMat{ {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}, 5.0f, SHADER_PATH "basicShader.hlsl" };
    m_cube = new Cube("SceneCube", cubeMat);

    m_scene.addRenderable(m_cube);
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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::sin(m_timer) * glm::two_pi<float>() * 0.5f, {1.0f, 1.0f, 1.0f});
    m_cube->setModel(model);

    Material cubeMat = *m_cube->getMaterial();
    cubeMat.m_shader.use();
    cubeMat.m_shader.setVec3("uColor", cubeMat.m_diff);
    cubeMat.m_shader.setMat4("uProj", m_proj);
    cubeMat.m_shader.setMat4("uView", *m_camera.getView());
    cubeMat.m_shader.setMat4("uModel", *m_cube->getModel());
    m_cube->getVao()->bind();
}

void Test3DLayer::onRender(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Test3DLayer::onImguiRender(void)
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}