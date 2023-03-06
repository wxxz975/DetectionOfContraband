#include "UI/Panels/PanelMenuBar.h"
#include <imgui/imgui.h>


void DcUI::Panels::PanelMenuBar::_Draw_Impl()
{
  if(!m_widgets.empty() && ImGui::BeginMainMenuBar())
  {
    DrawWidgets();
    ImGui::EndMainMenuBar();
  }
}

