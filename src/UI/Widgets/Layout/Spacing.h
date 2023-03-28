#pragma once 

#include "UI/Widgets/AWidget.h"


namespace DcUI::Widgets::Layout
{
  class Spacing: public AWidget
  {
    public:

      Spacing(uint16_t p_spaces = 1);

    protected:
      virtual void _Draw_Impl() override;

    public:
      uint16_t spaces = 1;
  };
}
