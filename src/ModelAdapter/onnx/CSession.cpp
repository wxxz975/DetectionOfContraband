#include "ModelAdapter/onnx/CSession.h"
#include <limits>
#include <algorithm>


void CSession::setRunningThread(int _num)
{
  this->intra_op_num_threads = _num;

}

CSession::CSession(const std::string& p_modelpath)
{
  env = Ort::Env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, envDefaultName.c_str());
  sessionOptions = Ort::SessionOptions();
  sessionOptions.SetIntraOpNumThreads(intra_op_num_threads);

  availableProviders = Ort::GetAvailableProviders();
  auto cudaAvailable = std::find(availableProviders.begin(), availableProviders.end(), "CUDAExecutionProvider");

  OrtCUDAProviderOptions cudaOption;
  cudaOption.device_id = 0;
  cudaOption.arena_extend_strategy = 0;
  cudaOption.gpu_mem_limit = std::numeric_limits<size_t>::max();
  cudaOption.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchExhaustive;
  cudaOption.do_copy_in_default_stream = 1;

  if (m_IsGPU && (cudaAvailable == availableProviders.end()))
  {
    std::cout << "GPU is not supported by your ONNXRuntime build. Fallback to CPU." << std::endl;
    std::cout << "Inference device: CPU" << std::endl;
  }
  else if (isGPU && (cudaAvailable != availableProviders.end()))
  {
    std::cout << "Inference device: GPU" << std::endl;
    sessionOptions.AppendExecutionProvider_CUDA(cudaOption);
  }
  else
  {
    std::cout << "Inference device: CPU" << std::endl;
  }

  std::cout << "model path:" << p_modelpath.c_str() << "\n";
  session = Ort::Session(env, p_modelpath.c_str(), sessionOptions);
  return true;

}
