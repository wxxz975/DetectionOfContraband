#pragma once

#include "Common/Eventing/Event.h"
#include "UI/Widgets/DataWidget.h"
#include "UI/Widgets/Sliders/ESliderOrientation.h"
#include <string>
#include <imgui/imgui.h>

namespace DcUI::Widgets::Sliders
{
  template<typename T>
  class SliderSingleScalar: public DataWidget<T>
  {
    static_assert(std::is_scalar<T>::value, "Invalid SliderSingleScalar T (Scalar expected)");
    
    public:
      /**
       * * Constructor
       * * @param p_dataType
       * * @param p_min
       * * @param p_max
       * * @param p_value
       * * @param p_orientation
       * * @param p_label
       * * @param p_format
       * */
      SliderSingleScalar(ImGuiDataType p_dataType,
         T p_min, T p_max, T p_value,
         ESliderOrientation p_orientation,
         const std::string& p_label, const std::string& p_format
        ) : DataWidget<T>(value), m_dataType(p_dataType), min(p_min), max(p_max), value(p_value), 
      orientation(p_orientation), label(p_label), format(p_format) {}
  
    public:
      T min;
      T max;
      T value;
      std::string label;
      std::string format;
      ESliderOrientation orientation;
    private:
      ImGuiDataType m_dataType;
  };
}
