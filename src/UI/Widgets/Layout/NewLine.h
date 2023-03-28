#pragma once

#include "UI/Widgets/AWidget.h"

namespace DcUI::Widgets::Layout
{
  class NewLine: public AWidget
  {
    protected:
      virtual void _Draw_Impl() override;
  };               

}
