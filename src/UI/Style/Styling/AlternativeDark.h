#pragma once
#include "UI/Style/Styling/AStyle.h"

namespace DcUI::Style::Styling
{
  class AlternativeDark: public AStyle
  {
    public:
      AlternativeDark() = default;
      virtual ~AlternativeDark() = default;


      virtual void apply() override;
  };

}
