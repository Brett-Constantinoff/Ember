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
    Transformation cubeTransform{ {-5.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::mat4(1.0f) };
    m_scene.addRenderable(new Cube("SceneCube0", cubeMat, cubeTransform));

    cubeMat.m_diff = { 0.0f, 0.0f, 1.0f };
    cubeTransform.m_translation = { 5.0f, 0.0f, 0.0f };
    m_scene.addRenderable(new Cube("SceneCube1", cubeMat, cubeTransform));

    cubeMat.m_diff = { 0.5f, 0.0f, 0.5f };
    cubeTransform.m_translation = { 0.0f, 5.0f, 0.0f };
    m_scene.addRenderable(new Cube("SceneCube2", cubeMat, cubeTransform));

    cubeMat.m_diff = { 0.5f, 0.5f, 0.0f };
    cubeTransform.m_translation = { 0.0f, -5.0f, 0.0f };
    m_scene.addRenderable(new Cube("SceneCube2", cubeMat, cubeTransform));

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
    m_scene.addCamera(new Camera({ 0.0f, 0.0f, 15.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }));
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