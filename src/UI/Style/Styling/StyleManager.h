#pragma once 

#include "UI/Style/Styling/AStyle.h"

namespace DcUI::Style
{

  class StyleManager/*: public CSingleton<StyleManager>*/
  {
    public:
      StyleManager() = default;
      ~StyleManager();

      void SetStyle(DcUI::Styling::EStyle _style);

    private:
      AStyle *style = nullptr;

  };
}
