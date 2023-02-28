#pragma once 
#include "AStyle.h"

class DuneDark: public AStyle
{
  public:
    DuneDark() = default;
    virtual ~DuneDark() = default;
    
    virtual void apply() override;
};
