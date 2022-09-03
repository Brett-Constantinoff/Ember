#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <sstream>
#include <string>
#include "../Math/glm.hpp"
#include "../Math/gtc/matrix_transform.hpp"
#include "Scene.h"
#include "../Core/Window.h"


struct RenderSettings
{
	bool m_blend;
	int32_t m_sFactorBlend = GL_SRC_ALPHA;
	int32_t m_dFactorBlend = GL_ONE_MINUS_SRC_ALPHA;
	glm::vec3 m_backgroundCol = { 0.25f, 0.25f, 0.25f };
	float m_depthValue = 1.0f;
	int32_t m_stencilValue = 0;
	bool m_clearStencil = false;
};

class Renderer
{
public:
	Renderer(RenderSettings settings);
	~Renderer();

	void render(Scene* scene);

private:
	void clear();

private:
	RenderSettings m_settings;
	Mesh* m_skyBox;
};