#pragma once
#include <imgui/imgui.h>
#include "UI/Style/Styling/Styling.h"

namespace DcUI::Style::Styling
{
  class AStyle
  {
    public:
      AStyle();
      virtual ~AStyle() = default;

      // apply the style
      virtual void apply() = 0;
  };
}
