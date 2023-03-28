#pragma once


#include "UI/Widgets/AWidget.h"
#include "UI/Internal/TextureID.h"

namespace DcUI::Widgets::Visual
{
  class Image: public AWidget
  {
    public:

      Image(uint32_t p_textureId, float p_width, float p_height);
    
    protected:
      virtual void _Draw_Impl() override;

    public:
      float width;
      float height;
      Internal::TextureID textureId;

  };

}
