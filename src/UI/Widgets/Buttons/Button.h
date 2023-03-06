#pragma once
#include <string>
#include <imgui/imgui.h>
#include "UI/Widgets/Buttons/AButton.h"
#include "UI/Types/Color.h"

namespace DcUI::Widgets::Buttons
{

  /*
   * Simple button widget
   * */
  class Button: public AButton
  {
    public:

    /*
     * Constructor
     * @param p_label
     * @param p_size
     * @param p_disabled
     * */
      Button(const std::string& p_label = "", 
          ImVec2 p_size = {0.f, 0.f}, 
          bool p_disabled = false);
  
    protected:
      void _Draw_Impl() override;

    public:
      std::string label;
      ImVec2 size;
      bool disabled = false;
      
      Types::Color idleBackgroundColor;
      Types::Color hoveredBackgroundColor;
      Types::Color clickedBackgroundColor;
     
      Types::Color textColor;
  };

}
