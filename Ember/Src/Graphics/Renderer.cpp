#include "Renderer.h"

Renderer::Renderer(RenderSettings settings) : 
	m_settings{settings}
{
	
	glEnable(GL_DEPTH_TEST);

	if (m_settings.m_blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(m_settings.m_sFactorBlend, m_settings.m_dFactorBlend);
	}
}

Renderer::~Renderer()
{

}

void Renderer::clear()
{
	GLbitfield field = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	if (m_settings.m_clearStencil)
	{
		field |= GL_STENCIL_BUFFER_BIT;
	}
	glClearColor(m_settings.m_backgroundCol.r, m_settings.m_backgroundCol.g, m_settings.m_backgroundCol.b, 1.0f);
	glClearDepth(m_settings.m_depthValue);
	glClearStencil(m_settings.m_stencilValue);
	glClear(field);
}

void Renderer::render(Scene* scene)
{
	clear();
	scene->render();
}
