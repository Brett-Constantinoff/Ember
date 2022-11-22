#include "ImguiLayer.h"

namespace Ember
{
    namespace Core
    {
        ImguiLayer::ImguiLayer(const char* name, Window* win) : Layer(name)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io; //sets up input / output

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(win->getContext(), true);
            ImGui_ImplOpenGL3_Init("#version 150");
            std::cout << "Creating " << m_name << std::endl;
        }

        ImguiLayer::~ImguiLayer()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            std::cout << "Destroying " << m_name << std::endl;
        }

        void ImguiLayer::onUpdate(float dt)
        {
            //setup imgui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void ImguiLayer::onRender()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
}
 