#include "UI/Core/UIManager.h"
#include <imgui/imgui_impl_opengl3.h>


DcUI::Core::UIManager::UIManager(GLFWwindow *p_glfwWinow, 
    DcUI::Style::Styling::EStyle p_style, 
    const std::string& p_glslVersion)
{
  ImGui::CreateContext();

  // disable moving window by dragging another thing than the title bar
  ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
  EnableDocking(false);

  
  ImGui_ImplGlfw_InitForOpenGL(p_glfwWinow, true);
  ImGui_ImplOpenGL3_Init(p_glslVersion.c_str());
}



DcUI::Core::UIManager::~UIManager()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}


