#pragma once
#include "UI/Panels/APanelTransformable.h"

namespace DcUI::Panels
{
  class PanelUndecorated: public APanelTransformable
  {
    public:
      virtual void _Draw_Impl() override;    
    
    private:
      int CollectFlags();
  }; 
}
