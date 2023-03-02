#pragma once
#include "Common/CSingleton.h"
#include <string>

enum class LoggingLevel
{
  LV_Debug,
  LV_Warning,
  LV_Release
};
// TODO: 

class ILogger
{
  public:
    ILogger(const std::string& outputPath);
    virtual ~ILogger() = default;
   
    virtual void log(const char* fmt, ...) = 0;
    virtual void log(const std::string& fmt, ...) = 0;

};
