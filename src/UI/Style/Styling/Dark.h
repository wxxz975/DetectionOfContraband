#pragma once

#include "UI/Style/Styling/AStyle.h"

namespace DcUI::Style::Styling
{
  class Dark: public AStyle
  {
    public:
      Dark() = default;
      virtual ~Dark() = default;

      virtual void apply() override;

  };
}
