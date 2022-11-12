#pragma once
#include "Engine.h"

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
	Scene m_scene;
};