#pragma once

#include "UI/Widgets/InputFields/InputMultipleScalar.h"

namespace DcUI::Widgets::InputFields
{
  template<size_t _Size>
  class InputMultipleDouble : public InputMultipleScalar<double, _Size>
  {
    public:
      InputMultipleDouble(
          double p_defaultValue = 0.0, double p_step = 0.1, double p_fastStep = 0.0,
          const std::string& p_label = "", const std::string& p_format = "%.6f",
          bool p_selctAllOnClick = true) : 
        InputMultipleScalar<double, _Size>(ImGuiDataType_Double, p_defaultValue, p_step, p_fastStep, 
            p_label, p_format, p_selctAllOnClick) {}
  };

}
