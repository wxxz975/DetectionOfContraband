#pragma once

#include <array>
#include <imgui/imgui.h>
#include "Common/Eventing/Event.h"
#include "UI/Widgets/DataWidget.h"

namespace DcUI::Widgets::InputFields
{
  template<typename T, size_t _Size>
    class InputMultipleScalar : public DataWidget<std::array<T, _Size>>
  {
    static_assert(_Size > 1, "Invalid InputMultipleScalar _Size (Must be greater than 1");
    static_assert(std::is_scalar<T>::value, "Invalid InputMultipleScalar T (Scalar required)");

    public:
      InputMultipleScalar(ImGuiDataType p_dataType, 
          const std::array<T, _Size>& p_defaultValue, 
          T p_step, T p_fastStep, const std::string& p_label, const std::string& p_format, 
          bool p_selctAllOnClick):
        DataWidget<std::array<T, _Size>>(values), m_dataType(p_dataType), 
        step(p_step), fastStep(p_fastStep), label(p_label), format(p_format), 
        selectAllOnClick(p_selctAllOnClick) {
          values.fill(p_defaultValue);
        };
    protected:
      virtual void _Draw_Impl() override;

    public:
      std::array<T, _Size> values;
      T step;
      T fastStep;
      std::string label;
      std::string format;
      bool selectAllOnClick;
      Common::Eventing::Event<std::array<T, _Size>&> ContentChangedEvent;
      Common::Eventing::Event<std::array<T, _Size>&> EnterPressedEvent;
    private:
      ImGuiDataType m_dataType;
  };
}
