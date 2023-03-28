#pragma once


#include "UI/Widgets/DataWidget.h"
#include "Common/Eventing/Event.h"
#include <string>

namespace DcUI::Widgets::Selection
{
  class RadioButton: public DataWidget<bool>
  {
    friend class RadioButtonLinker;

    public:
      RadioButton(bool p_selected = false, const std::string& p_label = "");

      /*
       * Make the radio button selected
       * */
      void Select();

      /*
       * Return true if the radio button selected
       * */
      bool IsSelected() const;
      
      /*
       * Return this radio button id
       * */
      bool GetRadioID() const;


    protected:
      virtual void _Draw_Impl() override;

    public:
      std::string label;
      Common::Eventing::Event<int> ClickedEvent;

    private:
      bool m_selected = false;
      int m_radioID = 0;
  };

}
