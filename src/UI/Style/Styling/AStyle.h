#pragma once
#include <imgui/imgui_draw.cpp>


class AStyle
{
  public:
    AStyle();
    virtual ~AStyle() = default;

    // apply the style
    virtual void apply() = 0;
};
