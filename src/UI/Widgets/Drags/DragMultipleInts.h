#pragma once

#include "UI/Widgets/Drags/DragMultipleScalars.h"

namespace DcUI::Widgets::Drags
{
  template<size_t _Size>
  class DragMultipleInts: public DragMultipleScalars<int, _Size>
  {
    public:
      /*
       * Constructor
       * @param 
       * */
      DragMultipleInts(
          int p_min,
          int p_max,
          int p_value,
          float p_speed,
          const std::string& p_label,
          const std::string& p_format
          ): DragMultipleScalars<int, _Size>(ImGuiDataType_::ImGuiDataType_S32, 
            p_min, p_max, p_value, p_speed, p_label, p_format)
    {};

  };

}
