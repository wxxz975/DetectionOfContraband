#pragma once

#include "UI/Widgets/Selection/RadioButton.h"

namespace DcUI::Widgets::Selection
{
  class RadioButtonLinker: public DataWidget<int>
  {
    public:
      /**
       * * Constructor
       * */
      RadioButtonLinker();

      /**
       * * Link the given radio button
       * */
      void Link(RadioButton& p_radioButton);

      /**
       * * Unlink the given radio button
       * */
      void Unlink(RadioButton& p_radioButton);

      /**
       * * Returns the id of the selected radio button
       * */
      int GetSelected() const;
  
    protected:
      virtual void _Draw_Impl() override;

    private:
      void OnRadioButtonClicked(int p_radioID);
  
    public:
      Common::Eventing::Event<int> ValueChangedEvent;

    private:
      int m_availableRadioID;
      int m_selected = -1;
      std::vector<std::pair<Common::Eventing::ListenerID, 
        std::reference_wrapper<RadioButton>>> m_radioButtons;

  };

}
