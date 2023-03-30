#pragma once

#include "Common/Eventing/Event.h"
#include "UI/Widgets/DataWidget.h"


namespace DcUI::Widgets::Menu
{
  class MenuItem: public DataWidget<bool>
  {
    public:
      MenuItem(const std::string& p_name, const std::string& p_shortcut = "", 
          bool p_checkable = false, bool p_checked = false);

    protected:
        virtual void _Draw_Impl() override;

    public:
      std::string name;
      std::string shortcut;
      bool checkable;
      bool checked;

      Common::Eventing::Event<> ClickedEvent;
      Common::Eventing::Event<bool> ValueChangedEvent;
      
    private:
      bool m_selected;
  };

}
