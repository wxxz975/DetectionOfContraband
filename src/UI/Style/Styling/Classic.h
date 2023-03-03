#pragma once 
#include "UI/Style/Styling/AStyle.h"


class Classic: public AStyle
{
  public: 
    Classic() = default;
    virtual ~Classic() = default;

    virtual void apply() override;
};
