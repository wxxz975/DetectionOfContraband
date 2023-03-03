#pragma once 

#include "UI/Style/Styling/AStyle.h"
class DuneDark: public AStyle
{
  public:
    DuneDark() = default;
    virtual ~DuneDark() = default;
    
    virtual void apply() override;
};
