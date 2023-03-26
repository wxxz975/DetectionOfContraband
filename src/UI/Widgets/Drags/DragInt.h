#pragma once

#include "UI/Widgets/Drags/DragSingleScalar.h"


namespace DcUI::Widgets::Drags
{
  class DragInt: public DragSingleScalar<int>
  { 
    public:
      /*
       * Constructor
       * @param p_min
       * @param p_max
       * @param p_value
       * @param p_lable
       * @param p_format
       * */
      DragInt(
          int p_min = 0,
          int p_max = 100,
          int p_value = 50,
          float p_speed = 1.f,
          const std::string& p_label = "",
          const std::string& p_format = "%d"
          );

  };
}
