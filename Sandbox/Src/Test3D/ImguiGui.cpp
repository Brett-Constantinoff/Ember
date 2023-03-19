#include "ImguiGui.h"

ImguiGui::ImguiGui(const Ember::Core::GuiCreateInfo& createInfo) :
	Gui{ createInfo }, m_selectedItem{true}, m_selectedIndex{0}
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
	ImGui::SetNextWindowSize(ImVec2(275, 258));

	// give it a title and make non-resizable and non-collapseable
	ImGui::Begin("Application Metrics", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	// display title
	ImGui::TextColored(ImVec4{ 0.678F, 0.847F, 0.902f, 1.0f }, "Application Metrics: ");

	//display the framerate
	ImGui::Text("Fps: %0.1f", ImGui::GetIO().Framerate);

	// display rendered objects
	ImGui::Text("Objects renderer: %d ",m_createInfo.m_scene->getEntityCount());

	// display rendered meshes
	ImGui::Text("Meshes renderer: %d ", m_createInfo.m_scene->getMeshCount());

	// display vertex count
	ImGui::Text("Total Vertices: %d ", m_createInfo.m_scene->getVertexCount());

	// display polygon count
	ImGui::Text("Total Trianlges: %d ", m_createInfo.m_scene->getPolygonCount());

	// end this component
	ImGui::End();
}

void ImguiGui::createSceneWindow()
{
	// get dimensions of the fps counter
	ImVec2 metricsSize{ ImGui::GetItemRectSize() };

	// set scene window to be the size of the metrics
	ImGui::SetNextWindowPos(ImVec2(0, 275));

	// get window size
	ImVec2 windowSize{ ImGui::GetWindowSize() };

	// fix the size
	ImGui::SetNextWindowSize(ImVec2(275, static_cast<int32_t>(m_createInfo.m_window->getHeight())));

	// give it a title and make non-resizable and non-collapseable
	ImGui::Begin("Scene Details", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

	// display title
	ImGui::TextColored(ImVec4{ 0.678F, 0.847F, 0.902f, 1.0f }, "Scene Details: ");

	// display camera location
	const auto& cameraPos = m_createInfo.m_scene->getCamera()->getPos();
	ImGui::Text("Camera Position: %.2fx %.2fy %.2fz ", cameraPos[0], cameraPos[1], cameraPos[2]);

	// display camera front
	const auto& cameraFront = m_createInfo.m_scene->getCamera()->getFront();
	ImGui::Text("Camera Front: %.2fx %.2fy %.2fz ", cameraFront[0], cameraFront[1], cameraFront[2]);

	// get scene entities
	const auto& entities{ m_createInfo.m_scene->getEntities() };

	// display each entity
	ImGui::SetCursorPosY(80);
	ImGui::Text("Entities");
	ImGui::SetNextItemWidth(275);
	ImGui::SetCursorPosY(100);
	if (ImGui::BeginListBox("##entity_list"));
	{
		for (int i = 0; i < entities.size(); i++)
		{
				m_selectedItem = (m_selectedIndex == i); //set the current selction
				if (ImGui::Selectable(entities[i]->getName().c_str(), m_selectedItem))
					m_selectedIndex = i;
		}
		ImGui::EndListBox();
	}

	// create details for selected entry
	ImGui::SetCursorPosY(250);
	const auto& entity{ entities[m_selectedIndex] };

	ImGui::SliderFloat3("Translation", &entity->getPosition().x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Scale", &entity->getScale().x, 0.1f, 10.0f);
	ImGui::SliderFloat3("Rotation", &entity->getRotationAxis().x, 0.0f, 1.0f);

	// display wireframe checkbox
	ImGui::Checkbox("Enable Wireframe", &entity->getWireFrame());

	// end this component
	ImGui::End();
}
