#pragma once
#include "UI/Types/Color.h"
#include <imgui/imgui.h>


namespace DcUI::Internal
{
  class Converter
  {
    public:

      Converter() = delete;

      static Types::Color ToColor(const ImVec4& p_value);

      static ImVec4 ToImVec4(const Types::Color& p_value);
  
      static ImVec2 ToImVec2(const )
  };
}
