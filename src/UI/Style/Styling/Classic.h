#pragma once 
#include "AStyle.h"


class Classic: public AStyle
{
  public: 
    Classic() = default;
    virtual ~Classic() = default;

    virtual void apply() override;
};
