#pragma once 
#include <memory>
#include "UI/Core/UIManager.h"
#include "OnnxModelAdapter/OnnxAlgorithm.h"
#include "Resources/ModelConfig.h"

namespace Core
{
  class Context
  {
    public:
      Context();
      
      /*
       * @brief: init the context, which contains the model config, UI config and the algorithm
       *         need a manager helper to initialized the pointer
       * @param: p_configPath: the path of the config file
       * @return: true if the context is initialized successfully, otherwise false
       * @description: the config file is a ini file, 
       *               which contains the model config path and UI config path of the application
       * */
      bool init(const std::string& p_configPath);
    public:
      
      
      std::unique_ptr<DcUI::Core::UIManager> m_uiManager;
      std::unique_ptr<OnnxModelAdapter::AbstractDetectAlgorithm> m_onnxAlgorithm;
      std::unique_ptr<Resources::ModelConfig> m_modelConfig;
  };
}
