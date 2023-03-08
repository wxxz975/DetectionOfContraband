#pragma once

#include <vector>
#include <string>
#include <core/session/onnxruntime_c_api.h>
#include "Resources/Model.h"

namespace Resources::Loaders
{
  class ModelLoader
  {
    public:
      ModelLoader() = delete; 
      
      static Model* LoadModel(const std::string& p_modelPath);

    private:
      std::vector<std::string> ParseClassNames(Ort::Session p_session);


  };
}
