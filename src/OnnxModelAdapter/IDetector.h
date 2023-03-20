#pragma once
#include <string>



class AResult
{
  public:
   AResult() = default; 
   virtual ~AResult() = 0;
};

class YOLOV5Result: public AResult
{

};

class IDetector
{
  public:
    IDetector() = default;
    virtual ~IDetector() = default;

    
  public:
    void detect();

};
