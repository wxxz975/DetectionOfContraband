#include "UI/Panels/PanelWindow.h"
#include "imgui/imgui_internal.h"
#include <imgui/imgui.h>

DcUI::Panels::PanelWindow::PanelWindow(
    const std::string& p_name, bool p_opened, 
    const Settings::PanelWindowSettings& p_floatingPanelSettings):
  name(p_name), 
  resizable(p_floatingPanelSettings.resizable), 
  closable(p_floatingPanelSettings.closable), 
  movable(p_floatingPanelSettings.movable),
  scrollable(p_floatingPanelSettings.scrollable), 
  dockable(p_floatingPanelSettings.dockable),
  hideBackground(p_floatingPanelSettings.hideBackground),
  forceHorizontalScrollbar(p_floatingPanelSettings.forceHorizontalScrollbar),
  forceVerticalScrollbar(p_floatingPanelSettings.forceVerticalScrollbar),
  bringToFrontOnFocus(p_floatingPanelSettings.bringToFrontOnFocus),
  collapsable(p_floatingPanelSettings.collapsable),
  allowInputs(p_floatingPanelSettings.allowInputs),
  m_opened(p_opened)
{
  autoSize = p_floatingPanelSettings.autoSize;
}


void DcUI::Panels::PanelWindow::Open()
{
  if(!m_opened)
  {
    m_opened = true;
    OpenEvent.Invoke();
  }
}

void DcUI::Panels::PanelWindow::Close()
{
  if(m_opened)
  {
    m_opened = false;
    CloseEvent.Invoke();
  }
}


void DcUI::Panels::PanelWindow::Focus()
{
  ImGui::SetWindowFocus((name + this->m_panelID).c_str()); 
}

void DcUI::Panels::PanelWindow::SetOpened(bool p_value)
{
  if(p_value != m_opened)
  {
    m_opened = p_value;

    if(m_opened)
      OpenEvent.Invoke();
    else
      CloseEvent.Invoke();
    
  }
}

bool DcUI::Panels::PanelWindow::IsOpened() const
{
  return m_opened;
}

bool DcUI::Panels::PanelWindow::IsHovered() const
{
  return m_hovered;
}

bool DcUI::Panels::PanelWindow::IsFocused() const
{
  return m_focused;
}

bool DcUI::Panels::PanelWindow::IsAppearing() const
{
  if(auto window = ImGui::FindWindowByName((name + this->m_panelID).c_str()); window)
    return window->Appearing;
  else 
    return false;
}


void DcUI::Panels::PanelWindow::ScrollToBotton()
{
  m_mustScrollToBotton = true;
}

void DcUI::Panels::PanelWindow::ScrollToTop()
{
  m_mustScrollToTop = false;
}

bool DcUI::Panels::PanelWindow::IsScrollToBotton() const
{
  return m_mustScrollToBotton;
}

bool DcUI::Panels::PanelWindow::IsScrollToTop() const
{
  return m_mustScrollToTop;
}


void DcUI::Panels::PanelWindow::_Draw_Impl()
{
  if(m_opened)
  {
    int windowFlags = ImGuiWindowFlags_None;

    if(!resizable)               windowFlags |= ImGuiWindowFlags_NoResize; 
    if(!movable)                 windowFlags |= ImGuiWindowFlags_NoMove;
    if(!dockable)                windowFlags |= ImGuiWindowFlags_NoDocking;
    if(hideBackground)           windowFlags |= ImGuiWindowFlags_NoBackground;
    if(forceVerticalScrollbar)   windowFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
    if(forceHorizontalScrollbar) windowFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar; 
    if(allowHorizontalScrollbar) windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
    
    if(!bringToFrontOnFocus)     windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if(!collapsable)             windowFlags |= ImGuiWindowFlags_NoCollapse;
    if(!allowInputs)             windowFlags |= ImGuiWindowFlags_NoInputs;
    if(!scrollable)              windowFlags |= ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
    if(!titleBar)                windowFlags |= ImGuiWindowFlags_NoTitleBar;

    ImVec2 minSizeConstraint = ImVec2(minSize[0], minSize[1]);
    ImVec2 maxSizeConstraint = ImVec2(maxSize[0], maxSize[1]);
    
    if(minSizeConstraint[0] <= 0.f || minSizeConstraint[1] < 0.f) 
      minSizeConstraint = { 0.0f, 0.0f };
    
    if(maxSizeConstraint[0] <= 0.f || maxSizeConstraint[1] < 0.f) 
      maxSizeConstraint = { 10000.f, 10000.f };
    
    ImGui::SetNextWindowSizeConstraints(minSizeConstraint, maxSizeConstraint);
    
    if(ImGui::Begin((name + m_panelID).c_str(), closable ? &m_opened : nullptr, windowFlags))
    {
      m_hovered = ImGui::IsWindowHovered();
      m_focused = ImGui::IsWindowFocused();
      
      auto scrollY = ImGui::GetScrollY();

      m_scrollToBotton = scrollY == ImGui::GetScrollMaxY();
      m_scrollToTop = scrollY == 0.0f;

      if(!m_opened)
        CloseEvent.Invoke();

      Update();

      if(m_mustScrollToBotton)
      {
        ImGui::SetScrollY(ImGui::GetScrollMaxY());
        m_mustScrollToBotton = false;
      }

      if(m_mustScrollToTop)
      {
        ImGui::SetScrollY(0.0f);
        m_mustScrollToTop = false;
      }
      
      DrawWidgets(); 
    }
    ImGui::End();
  }
}
