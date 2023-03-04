#include "UI/Panels/APanel.h"
#include <algorithm>

uint64_t DcUI::Panels::APanel::__PANEL_ID_INCREMENT = 0;

DcUI::Panels::APanel::APanel()
{
  m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
}

void DcUI::Panels::APanel::Draw()
{
  if(enabled)
    _Draw_Impl();
}

const std::string& DcUI::Panels::APanel::GetPanelID() const 
{
  return m_panelID;
}


