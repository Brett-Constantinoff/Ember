#pragma once
#include "Engine.h"

class Test3DLayer : public Ember::Core::Layer
{
public:
	Test3DLayer(const char* name);
	~Test3DLayer();

	virtual void onAttach(Ember::Core::Window* win);
	virtual void onDetach();
	virtual void onUpdate(float dt);
	virtual void onRender();
	virtual void onImguiRender();

private:
	Ember::Core::Window * m_win;
	Ember::Scene::Scene3D m_scene;
};