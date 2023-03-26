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
      Session(const std::string& p_modelPath, bool isGPU = true);
      ~Session() = default;
    
      // return default allocator 
      inline const Ort::AllocatorWithDefaultOptions& GetAllocator() const {
        return m_allocator;
      };
      
      inline const Ort::MemoryInfo& GetMemoryInfo() const {
        return m_pMemoryInfo;
      }

      // return model pointer
      inline const std::shared_ptr<Model> GetModel() const {
        return m_pMod;
      };

    public:
      Ort::Session m_pSession{nullptr};
    private:
      
      
      Ort::Env env{nullptr};

      Ort::SessionOptions m_pSessionOpt;
      
      Ort::AllocatorWithDefaultOptions m_allocator;
      
      Ort::MemoryInfo m_pMemoryInfo{nullptr};  
      
      const std::string m_EnvDefaultName = "envName";
      const std::string m_pModelPath = "x_ray.onnx"; // default 
      
      int m_intra_op_num_threads = 4; 
      bool m_IsGPU = true; 
      
      std::shared_ptr<Model> m_pMod = nullptr;   
  };

}
