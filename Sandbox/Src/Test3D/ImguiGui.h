#pragma once
#include <Engine.h>

class ImguiGui : public Ember::Core::Gui
{
public:
	ImguiGui(const Ember::Core::GuiCreateInfo& createInfo);
	virtual ~ImguiGui();

	virtual void update();
	virtual void render();

private:
	virtual void init();
	void createMenuBar();
	void createFpsCounter();
	void createSceneWindow();
};