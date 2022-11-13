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

    Material cubeMat0{ {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.1f}, 5.0f, SHADER_PATH "directionalLighting.hlsl", true};
    Transformation cubeTransform0{ {-5.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::mat4(1.0f) };
    m_scene.addRenderable(new Cube("SceneCube0", cubeMat0, cubeTransform0));

    Material cubeMat1{ {0.0f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.1f}, 10.0f, SHADER_PATH "directionalLighting.hlsl", true };
    Transformation cubeTransform1{ {5.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::mat4(1.0f) };
    m_scene.addRenderable(new Cube("SceneCube1", cubeMat1, cubeTransform1));

    Material cubeMat2{ {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.1f}, 15.0f, SHADER_PATH "flatShading.hlsl", false };
    Transformation cubeTransform2{ {0.0f, 5.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::mat4(1.0f) };
    m_scene.addRenderable(new Cube("SceneCube2", cubeMat2, cubeTransform2));

    Material cubeMat3{ {1.0f, 0.0f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.1f}, 20.0f, SHADER_PATH "flatShading.hlsl", false };
    Transformation cubeTransform3{ {0.0f, -5.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, glm::mat4(1.0f) };
    m_scene.addRenderable(new Cube("SceneCube3", cubeMat3, cubeTransform3));

    Material quadMat{ {0.25f, 0.25f, 0.25f}, {0.25f, 0.25f, 0.25f}, {0.1f, 0.1f, 0.1f}, 5.0f, SHADER_PATH "directionalLighting.hlsl", true };
    Transformation quadTransform{ {0.0f, -7.5f, 0.0f}, {50.0f, 50.0f, 50.0f}, glm::mat4(1.0f) };
    Quad* quad = new Quad("SceneFloor", quadMat, quadTransform);
    glm::vec3 rotAxis = { 1.0f, 0.0f, 0.0f };
    m_scene.addRenderable(quad);

    m_scene.addDirLight(new DirectionalLight{ {-0.2f, -1.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f} });

    std::vector<const char*> skyboxFiles = {
        SKYBOX_PATH "right.jpg",
        SKYBOX_PATH "left.jpg",
        SKYBOX_PATH "top.jpg",
        SKYBOX_PATH "bottom.jpg",
        SKYBOX_PATH "front.jpg",
        SKYBOX_PATH "back.jpg",
    };
    Material skyboxMat{ {}, {}, {}, 0.0f, SHADER_PATH "skyboxShader.hlsl", false };
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