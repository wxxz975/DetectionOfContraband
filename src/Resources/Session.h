#pragma once 

#include <algorithm>
#include <string>
#include <core/session/onnxruntime_cxx_api.h>
#include "Resources/Model.h"

namespace Resources
{
  class Session
  {
    public:
      Session(const std::string& p_modelPath);
      ~Session() = default;
    
      // return default allocator 
      const Ort::AllocatorWithDefaultOptions& GetAllocator() const;


    private:
      
      Ort::Session m_pSession{nullptr};
      
      Ort::Env env{nullptr};

      Ort::SessionOptions m_pSessionOpt;
      
      Ort::AllocatorWithDefaultOptions m_allocator;
      
      Ort::MemoryInfo m_pMemoryInfo{nullptr};  
      
      const std::string m_EnvDefaultName = "envName";
      const std::string m_pModelPath = "x_ray.onnx"; // default 
      
      int m_intra_op_num_threads = 4; 
      bool m_IsGPU = true; 
      
      std::unique_ptr<Model> m_pMod = nullptr;   
  };

}
