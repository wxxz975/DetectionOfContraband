#pragma once

#include <imgui/imgui.h>
#include "UI/Types/Color.h"
#include "UI/Widgets/Buttons/AButton.h"
#include "UI/Internal/TextureID.h"


namespace DcUI::Widgets::Buttons
{
  class ButtonImage: public AButton
  {
    public:
      /*
       * Constructor
       * @param p_textureID
       * @param p_size
       * */
      ButtonImage(uint32_t p_textureID, const ImVec2& p_size);
      
      ~ButtonImage() {};
      
    protected:
      
      void _Draw_Impl() override;  
    
    public:
      
      bool disabled;
      Types::Color background = {0, 0, 0, 0};
      Types::Color tint = {1, 1, 1, 1};
      
      Internal::TextureID textureID; 
  };
}
