#pragma once

#include "UI/Widgets/InputFields/InputMultipleScalar.h"
#include <cwchar>

namespace DcUI::Widgets::InputFields
{
  template<size_t _Size>
  class InputMultipleInt : public InputMultipleScalar<int, _Size>
  {
    public:
      InputMultipleInt(
          int p_defaultValue = 0, int p_step = 1, int p_fastStep = 0,
          const std::string& p_label = "", const std::string& p_format = "%d",
          bool p_selctAllOnClick = true) : 
        InputMultipleScalar<int, _Size>(ImGuiDataType_S32, p_defaultValue, p_step, p_fastStep, 
            p_label, p_format, p_selctAllOnClick) {}
  };

}
