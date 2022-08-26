#pragma once
#include "GL/glew.h"
#include "../Math/glm.hpp"
#include "Scene.h"

struct RenderSettings
{
	bool m_blend;
	int32_t m_sFactorBlend = GL_SRC_ALPHA;
	int32_t m_dFactorBlend = GL_ONE_MINUS_SRC_ALPHA;
	glm::vec3 m_backgroundCol = { 0.25f, 0.25f, 0.25f };
	float m_depthValue = 1.0f;
	int32_t m_stencilValue = 0;
	bool m_clearColor = true;
	bool m_clearDepth = true;
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
};