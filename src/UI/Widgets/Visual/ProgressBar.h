#pragma once

#include "UI/Widgets/AWidget.h"

namespace DcUI::Widgets::Visual
{
  class ProgressBar: public AWidget
  {
    public:
      ProgressBar(float p_fraction = 0.0f, 
          float  p_width = 0.0f, float p_height = 0.0f, const std::string& p_overlay = "");
    
    protected:
      virtual void _Draw_Impl() override;

    public:
      float fraction;
      float width, height;
      std::string overlay; 
  
  };
}
