#pragma once

#include "Common/Eventing/Event.h"
#include "UI/Widgets/DataWidget.h"
#include <string>


namespace DcUI::Widgets::Selection
{
  class CheckBox: public DataWidget<bool>
  {
    public:
      /*
       * Constructor
       * @param p_value
       * @param p_label
       * */
      CheckBox(bool p_value = false, const std::string& p_label = "");
       
    protected:  
      virtual void _Draw_Impl() override;
    
    public:
      bool value;
      std::string label;
      Common::Eventing::Event<bool> ValueChangedEvent;
  };

}
