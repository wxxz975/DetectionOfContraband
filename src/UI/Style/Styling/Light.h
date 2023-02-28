#pragma once
#include "AStyle.h"

class Light: public AStyle
{
  public:
    Light() = default;
    virtual ~Light() = default;

    virtual void apply() override;
};
