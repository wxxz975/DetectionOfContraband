#include "OnnxModelAdapter/OnnxAlgorithm.h"


const std::vector<std::vector<ResultNode>> 
OnnxModelAdapter::OnnxAlgorithm::detect(const std::vector<cv::Mat> &images)
{
  
  const auto& memInfo = m_pSession->GetMemoryInfo();
  const auto& model = m_pSession->GetModel();
  const auto& inputDims = model->GetInputDimension();
  const auto& outputDims = model->GetOutputDimension(); 
  auto& blobs = model->GetInputPtr();
  const auto& inputNames = model->GetInputNames();
  const auto& outputNames = model->GetOutputNames();

  std::vector<Ort::Value> inputTensors;
  // preprocessing
  for(size_t idx = 0; idx < images.size(); ++idx)
  {
    m_prepro->Impl(images[idx], inputDims[idx]->Shape, blobs[idx]); 
    
    std::vector<float>inputTensorValues(blobs[idx], blobs[idx] + inputDims[idx]->Size);
      
    inputTensors.push_back(Ort::Value::CreateTensor<float>(memInfo, 
          inputTensorValues.data(), inputTensorValues.size(), 
          inputDims[idx]->Shape.data(), inputDims[idx]->Shape.size())); 
  }
  
  std::vector<Ort::Value> outputTensors = m_pSession->m_pSession.Run(
      Ort::RunOptions{nullptr}, 
      inputNames.data(), 
      inputTensors.data(), inputTensors.size(),
      outputNames.data(), outputNames.size());

  
  std::vector<std::vector<ResultNode>> results;
  // postprocessing
  for(size_t idx = 0; idx < outputTensors.size(); ++idx)
  {
    const auto& shape = outputDims[idx]->Shape;
    
    cv::Size resizedShape = cv::Size((int)shape[3], (int)shape[2]);
    cv::Size originalShape = images[idx].size();
    auto result = m_postpro->Impl(
        outputTensors[idx],
        resizedShape, originalShape,
        confThreshold, iouThreshold);
    
    
    results.push_back(result);
  }
  
  return results;
}

bool OnnxModelAdapter::OnnxAlgorithm::InitModel(const std::string& p_modelPath)
{
  // default use gpu Inference
  m_pSession = std::make_unique<Resources::Session>(p_modelPath);

  return true;
}
