#pragma once

#include <vector>
#include <string>
#include <core/session/onnxruntime_c_api.h>
#include "Resources/Model.h"

namespace Resources
{
  class ModelLoader
  {
    public:
      ModelLoader() = delete; 
      
      static Model* LoadModel(const Ort::Session& p_session);

    private:
      static std::vector<std::string> ParseClassNames(const Ort::Session& p_session);
    
  };
}
