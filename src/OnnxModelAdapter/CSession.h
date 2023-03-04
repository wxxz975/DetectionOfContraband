#pragma once
#include <core/session/onnxruntime_cxx_api.h>
#include <string>
#include <vector> 
#include <memory>

class CSession
{
  public:
    CSession(const std::string& p_modelpath);
    ~CSession() = default;


    void setRunningThread(int _num);
     
  private: 
    

    std::unique_ptr<Ort::Session> m_pSession;
    Ort::Env env{nullptr};
    std::string envDefaultName = "OnnxDetection";
    Ort::SessionOptions sessionOptions{nullptr};
    //Ort::MemoryInfo memoryInfo;
    Ort::AllocatorWithDefaultOptions allocator;

    std::vector<std::string> availableProviders;
    
    int intra_op_num_threads = 5;
    
    bool m_IsGPU = true;

};
