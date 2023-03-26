#pragma once

#include <array>
#include <imgui/imgui.h>
#include "Common/Eventing/Event.h"
#include "UI/Widgets/DataWidget.h"

namespace DcUI::Widgets::Drags
{
  template<typename T, size_t _Size>
  class DragMultipleScalars: public DataWidget<std::array<T, _Size>>
  {
    static_assert(_Size > 1, "Invalid DragMultipleScalars _Size (2 or more required)");
    
    public:
      /*
       * Constructor
       * @param p_dataType
       * @param p_min
       * @param p_max
       * @param p_speed
       * @param p_label
       * @param p_format
       * */
    DragMultipleScalars(ImGuiDataType_ p_dataType, T p_min, T p_max, T p_value, float p_speed,
        const std::string& p_label, const std::string& p_format):
      DataWidget<std::array<T, _Size>>(values), m_dataType(p_dataType), 
      min(p_min), max(p_max), speed(p_speed), label(p_label), format(p_format)
    {
      values.fill(p_value); 
    }

    protected:
      virtual void _Draw_Impl() override
      {
        if(max < min) 
          max = min;

        for(size_t i; i < _Size; ++i)
        {
          if(values[i] < min)
            values[i] = min;
          else if (values[i] > max)
            values[i] = max;
        }

        if(ImGui::DragScalarN((label + this->m_widgetID).c_str(), 
              m_dataType, values.data(), _Size, speed, &min, &max, format.c_str()))
        {
          ValueChangedEvent.Invoke(values);
          this->NotifyChange();
        }

      }
    public:
      T min;
      T max;
      std::array<T, _Size> values;
      float speed;
      std::string label;
      std::string format;
      Common::Eventing::Event<std::array<T, _Size>&> ValueChangedEvent;
    
    private:
      ImGuiDataType_ m_dataType;
  };

}
