#pragma once 

#include <map>
#include <string>
#include "UI/Widgets/DataWidget.h"
#include "Common/Eventing/Event.h"

namespace DcUI::Widgets::Selection
{
  class ComboBox: public DataWidget<int>
  {
    public:
      ComboBox(int p_currentChoice = 0);

    protected:
      virtual void _Draw_Impl() override;

    public:
      std::map<int, std::string> choices;
      int currentChoice;

    public:
      Common::Eventing::Event<int> ValueChangedEvent;
  };

}
