#pragma once

#include "UI/Style/Styling/AStyle.h"

class Light: public AStyle
{
  public:
    Light() = default;
    virtual ~Light() = default;

    virtual void apply() override;
};
