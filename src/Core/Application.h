#pragma once

#include <string>
#include "Core/Context.h"

namespace Core
{
  class Application
  {
    public:
      Application();
      ~Application() = default;


      /*
       * @brief: run the application
       * @param: p_configPath: the path of the config file
       * * @description: the config file is a ini file, 
       *               which contains the model config path and UI config path of the application
       * */
      void run(const std::string& p_configPath);

    private:
      void preprocess() const;
      void postprocess() const;

    private:
      std::unique_ptr<Context> m_context;
  };
}
