#include "Resources/Session.h"
#include "Resources/Loaders/ModelLoader.h"
#include <algorithm>


#define DEBUG
#ifdef DEBUG
#include <iostream>
#else
#include "Common/Logger/TXTLogger.h"
#endif

Resources::Session::Session(const std::string &p_modelPath): 
  m_pModelPath(p_modelPath)
                                                             
{
    env = Ort::Env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, m_EnvDefaultName.c_str());
    m_pSessionOpt = Ort::SessionOptions();
    m_pSessionOpt.SetIntraOpNumThreads(m_intra_op_num_threads);

    std::vector<std::string> availableProviders = Ort::GetAvailableProviders();
    auto cudaAvailable = std::find(availableProviders.begin(), availableProviders.end(), 
        "CUDAExecutionProvider");
    
    OrtCUDAProviderOptions cudaOption;
    cudaOption.device_id = 0;
    cudaOption.arena_extend_strategy = 0;
    cudaOption.gpu_mem_limit = std::numeric_limits<size_t>::max();
    cudaOption.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchDefault;
    cudaOption.do_copy_in_default_stream = 1;

    if (m_IsGPU && (cudaAvailable == availableProviders.end()))
    {
        std::cout << 
          "GPU is not supported by your ONNXRuntime build. Fallback to CPU.\n";
        std::cout << "Inference device: CPU\n";
    }
    else if (m_IsGPU && (cudaAvailable != availableProviders.end()))
    {
        std::cout << "Inference device: GPU\n";
        m_pSessionOpt.AppendExecutionProvider_CUDA(cudaOption);
    }
    else
    {
        std::cout << "Inference device: CPU\n";
    }

    std::cout << "model path:" << m_pModelPath.c_str() << "\n";
    m_pSession = Ort::Session(env, m_pModelPath.c_str(), m_pSessionOpt);
  
    m_pMod = ModelLoader::LoadModel(m_pSession);

    
}


const Ort::AllocatorWithDefaultOptions& Resources::Session::GetAllocator() const
{
  return m_allocator;
}
