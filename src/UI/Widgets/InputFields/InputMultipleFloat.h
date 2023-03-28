#pragma once

#include "UI/Widgets/InputFields/InputMultipleScalar.h"


namespace DcUI::Widgets::InputFields
{
  template<size_t _Size>
  class InputMultipleFloat : public InputMultipleScalar<float, _Size>
  {
    public:
      InputMultipleFloat(
          float p_defaultValue = 0.0f, float p_step = 0.1f, float p_fastStep = 0.0f,
          const std::string& p_label = "", const std::string& p_format = "%.3f",
          bool p_selctAllOnClick = true) : 
        InputMultipleScalar<float, _Size>(ImGuiDataType_Float, p_defaultValue, p_step, p_fastStep, 
            p_label, p_format, p_selctAllOnClick) {}
  };

}
