#pragma once 
#include "UI/Style/Styling/AStyle.h"

namespace DcUI::Style::Styling
{
  class Classic: public AStyle
  {
    public: 
      Classic() = default;
      virtual ~Classic() = default;

      virtual void apply() override;
  };
}
