#pragma once


#include "UI/Panels/APanel.h"


namespace DcUI::Panels
{
  
  class PanelMenuBar: public APanel
  {
    protected:
      void _Draw_Impl() override;
  };
}
