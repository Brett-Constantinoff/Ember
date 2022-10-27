#pragma once
#include "Engine.h"
#define THREE_DIM

class Test3DLayer : public Layer
{
public:
	Test3DLayer(const char* name);
	~Test3DLayer();

	virtual void onAttach(Window* win);
	virtual void onDetach();
	virtual void onUpdate(float dt);
	virtual void onRender();
	virtual void onImguiRender();

private:
	Window* m_win;
	Shader* m_shader;
	Camera* m_camera;
	VertexArray* m_vao;
	VertexBuffer* m_vbo;
	VertexBuffer* m_colorBuffer;
	uint32_t vao;
	glm::mat4 m_proj;
	glm::mat4 m_cubeModel;
	float m_timer;
};