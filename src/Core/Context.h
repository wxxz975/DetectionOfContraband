#pragma once 
#include <memory>
#include "UI/Core/UIManager.h"
#include "OnnxModelAdapter/OnnxAlgorithm.h"

namespace Core
{
  class Context
  {
    public:
      Context();
      
    
    private:
      std::unique_ptr<DcUI::Core::UIManager> m_uiManager;
      std::unique_ptr<OnnxModelAdapter::AbstractDetectAlgorithm> m_onnxAlgorithm;
    
  };
}
