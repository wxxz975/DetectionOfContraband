#include "UI/Widgets/Visual/ProgressBar.h"
#include <imgui/imgui.h>


DcUI::Widgets::Visual::ProgressBar::ProgressBar(
    float p_fraction, float p_width, float p_height, const std::string& p_overlay
    ): fraction(p_fraction), width(p_width), height(p_height), overlay(p_overlay)
{
   
}

void DcUI::Widgets::Visual::ProgressBar::_Draw_Impl()
{
  ImGui::ProgressBar(fraction, {width, height}, !overlay.empty() ? overlay.c_str() : nullptr);
}
