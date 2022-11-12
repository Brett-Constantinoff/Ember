#include "Test3DLayer.h"

Test3DLayer::Test3DLayer(const char* name) : 
    Layer(name), m_win{nullptr}
{
}

Test3DLayer::~Test3DLayer()
{
}

void Test3DLayer::onAttach(Window* win)
{
	m_win = win;

    Material cubeMat{ {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}, 5.0f, SHADER_PATH "basicShader.hlsl" };
    m_scene.addRenderable(new Cube("SceneCube", cubeMat));
    std::vector<const char*> skyboxFiles = {
        SKYBOX_PATH "right.jpg",
        SKYBOX_PATH "left.jpg",
        SKYBOX_PATH "top.jpg",
        SKYBOX_PATH "bottom.jpg",
        SKYBOX_PATH "front.jpg",
        SKYBOX_PATH "back.jpg",
    };
    Material skyboxMat{ {}, {}, {}, 0.0f, SHADER_PATH "skyboxShader.hlsl" };
    m_scene.addSkyBox(new SkyBox("skybox", skyboxMat, skyboxFiles));
    m_scene.addCamera(new Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }));
    m_scene.addContext(m_win);
}

void Test3DLayer::onDetach(void)
{

}

void Test3DLayer::onUpdate(float dt)
{
    m_scene.update(dt);
}

void Test3DLayer::onRender(void)
{
    m_scene.render();
}

void Test3DLayer::onImguiRender(void)
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}