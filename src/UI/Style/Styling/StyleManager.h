#pragma once 

#include "UI/Style/Styling/AStyle.h"

namespace DcUI::Style::Styling
{

  class StyleManager/*: public CSingleton<StyleManager>*/
  {
    public:
      StyleManager() = default;
      ~StyleManager();

      void SetStyle(Styling::EStyle _style);

    private:
      AStyle *style = nullptr;

  };
}
