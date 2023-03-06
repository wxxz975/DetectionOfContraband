#pragma once

#include "UI/Widgets/AWidget.h"
#include "Common/Eventing/Event.h"

namespace DcUI::Widgets::Buttons
{
  /*
   * Base clas for any button widget
   * */ 
  class AButton: public AWidget
  {
    protected:
      void _Draw_Impl() override = 0;
    
    public:
      Common::Eventing::Event<> ClickedEvent;
  };

}
