#pragma once

#include "AStyle.h"


class AlternativeDark: public AStyle
{
  public:
    AlternativeDark() = default;
    virtual ~AlternativeDark() = default;


    virtual void apply() override;
};
