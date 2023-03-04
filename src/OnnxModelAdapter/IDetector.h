#pragma once
#include <string>


class IDetector
{
  public:
    IDetector() = default;
    virtual ~IDetector() = default;

    
  public:
    detect();

};
