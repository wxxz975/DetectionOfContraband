#include "StyleManager.h"

#include "UI/Style/Styling/AStyle.h"

#include "UI/Style/Styling/Classic.h"
#include "UI/Style/Styling/Dark.h"
#include "UI/Style/Styling/Light.h"

#include "UI/Style/Styling/AlternativeDark.h"
#include "UI/Style/Styling/DuneDark.h"

DcUI::Style::StyleManager::~StyleManager()
{
  if(style != nullptr) {
    delete style;
    style = nullptr;
  }
}


// TODO: this violate opening and closing  principle
void DcUI::Style::StyleManager::SetStyle(DcUI::Styling::EStyle _style)
{
  if(style != nullptr) delete style;
  
  switch(_style)
  {
    case DcUI::Styling::EStyle::IM_CLASSIC_STYLE:
      {
        style = new Classic();
      }
    case DcUI::Styling::EStyle::IM_DARK_STYLE:
      {
        style = new Dark();
      }
    case DcUI::Styling::EStyle::IM_LIGHT_STYLE:
      {
        style = new Light();
      }
    case DcUI::Styling::EStyle::DUNE_DARK_STYLE:
      {
        style = new DuneDark();
      }
    case DcUI::Styling::EStyle::ALTERNATIVE_DARK:
      {
        style = new AlternativeDark();
      }
    default:
      style = nullptr; // default style
  }

  return style->apply();
}


