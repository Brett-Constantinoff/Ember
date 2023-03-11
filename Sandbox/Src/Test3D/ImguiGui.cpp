#include "ImguiGui.h"

ImguiGui::ImguiGui(const Ember::Core::GuiCreateInfo& createInfo) :
	Gui{ createInfo }
{
	init();
}

ImguiGui::~ImguiGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiGui::init()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(*m_createInfo.m_window->getContext(), true);
	ImGui_ImplOpenGL3_Init("#version 150");
}

void ImguiGui::update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImguiGui::render()
{
	// gui components go here
	createMenuBar();
	createFpsCounter();
	createSceneWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiGui::createMenuBar()
{
	ImGui::BeginMainMenuBar();

	// menu bar items go between these lines
	if (ImGui::BeginMenu("Ember"))
	{
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void ImguiGui::createFpsCounter()
{
	// get previous size of menu
	ImVec2 menuSize{ ImGui::GetItemRectSize() };

	// set metrics window to lineup with menu bar
	ImGui::SetNextWindowPos(ImVec2(0, menuSize[1] - 1));

	// fix the size
	ImGui::SetNextWindowSize(ImVec2(250, 250));

	// give it a title and make non-resizable and non-collapseable
	ImGui::Begin("Application Metrics", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	// display title
	ImGui::TextColored(ImVec4{ 0.678F, 0.847F, 0.902f, 1.0f }, "Application Metrics: ");

	//display the framerate
	ImGui::Text("Fps: %0.1f", ImGui::GetIO().Framerate);

	// display rendered objects
	ImGui::Text("Objects renderer: %d ",m_createInfo.m_scene->getRenderCount());

	// end this component
	ImGui::End();
}

void ImguiGui::createSceneWindow()
{
	// get dimensions of the fps counter
	ImVec2 metricsSize{ ImGui::GetItemRectSize() };

	// set scene window to be the size of the metrics
	ImGui::SetNextWindowPos(ImVec2(0, 250));

	// get window size
	ImVec2 windowSize{ ImGui::GetWindowSize() };

	// fix the size
	ImGui::SetNextWindowSize(ImVec2(250, m_createInfo.m_window->getHeight()));

	// give it a title and make non-resizable and non-collapseable
	ImGui::Begin("Scene Details", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	// display title
	ImGui::TextColored(ImVec4{ 0.678F, 0.847F, 0.902f, 1.0f }, "Scene Details: ");

	// end this component
	ImGui::End();
}