#pragma once 
//#include "Common/CSingleton.h"

#include "UI/Style/Styling/AStyle.h"
#include <string>


class StyleManager/*: public CSingleton<StyleManager>*/
{
  public:
    StyleManager() = default;
    ~StyleManager();

    void SetStyle(DcUI::Styling::EStyle _style);

  private:
    AStyle *style = nullptr;
 
};

