#pragma once

#include "UI/Widgets/AWidget.h"

namespace DcUI::Widgets::Visual
{
  /*
   * Sample widgets that display a Separator
   * */ 
  class Separator: public AWidget
  {
    protected:
      virtual void _Draw_Impl() override;
  };

}
