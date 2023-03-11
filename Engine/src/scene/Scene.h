#pragma once
#include "../renderer/Shader.h"
#include "Camera.h"
#include <stdint.h>
#include <memory>

namespace Ember::Scene
{
	struct SceneCreateInfo
	{
		Ember::Scene::Camera* m_camera{};
		Ember::Renderer::Shader* m_shader{};
		GLFWwindow* m_windowContext{};
	};

	class Scene
	{
	public:
		Scene(const SceneCreateInfo& createInfo);
		~Scene();

		void createCube();
		uint32_t getCube() const;
		Ember::Scene::Camera* getCamera() const;
		Ember::Renderer::Shader* getShader() const;

	private:
		SceneCreateInfo m_createInfo;
		uint32_t m_vao;
		uint32_t m_vbo;
	};
}