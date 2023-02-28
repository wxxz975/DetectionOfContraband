#pragma once
#include "AStyle.h"


class Dark: public AStyle
{
  public:
    Dark() = default;
    virtual ~Dark() = default;

    virtual void apply() override;

};
