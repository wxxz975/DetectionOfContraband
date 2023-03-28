#include "UI/Widgets/Visual/Image.h"
#include <imgui/imgui.h>


DcUI::Widgets::Visual::Image::Image(
    uint32_t p_textureId, float p_width, float p_height
    ): textureId{p_textureId}, width(p_width), height(p_height)
{

}

void DcUI::Widgets::Visual::Image::_Draw_Impl()
{
  ImGui::Image(textureId.raw, {width, height});
}
