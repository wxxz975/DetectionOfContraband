#include "UI/Core/UIManager.h"
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

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

void DcUI::Core::UIManager::EnableDocking(bool p_value)
{
  m_dockingState = p_value;
  
  if(p_value)
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  else
    ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
}

void DcUI::Core::UIManager::ApplyStyle(Style::Styling::EStyle p_style)
{
  m_styleMgr.SetStyle(p_style);  
}

DcUI::Style::FontManager& DcUI::Core::UIManager::GetFontManager()
{
  return m_fontMgr;
}


void DcUI::Core::UIManager::SetCanvas(Modules::Canvas& p_canvas)
{
  RemoveCanvas();

  m_currentCanvas = &p_canvas;
}


void DcUI::Core::UIManager::RemoveCanvas()
{
  m_currentCanvas = nullptr;
}

void DcUI::Core::UIManager::Render()
{
  if(m_currentCanvas)
  {
    m_currentCanvas->Draw();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
}

