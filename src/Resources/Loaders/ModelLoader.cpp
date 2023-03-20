#include "Resources/Loaders/ModelLoader.h"


Resources::Model* Resources::ModelLoader::LoadModel(const Ort::Session& p_session)
{
  auto labels = ModelLoader::ParseClassNames(p_session);
  Ort::AllocatorWithDefaultOptions allocator;

  size_t inputCount = p_session.GetInputCount();
  size_t outputCount = p_session.GetOutputCount();
  
  Model::Blobs blobs;

  std::vector<Model::OneDimension> inputDim(inputCount);
  std::vector<Model::OneDimension> outputDim(outputCount);
  for(size_t idx = 0; idx < inputCount; ++idx) {

    const char* inputname = p_session.GetInputName(idx, allocator);
    
    Ort::TypeInfo inputTypeInfo = p_session.GetInputTypeInfo(idx); 
    
    auto TypeAndShape = inputTypeInfo.GetTensorTypeAndShapeInfo();
    
    //ONNXTensorElementDataType eleType = TypeAndShape.GetElementType(); 
    std::vector<int64_t> tenShape = TypeAndShape.GetShape();
    
    inputDim.push_back(std::make_shared<DimensionInfomation>(inputname, tenShape));
    blobs.push_back(new float[inputDim.back().get()->Size]);
  }

  //std::cout << "output dimension: " << outputCount << "\n";
  for(size_t idx = 0; idx < outputCount; ++idx) {
    char* outputName = p_session.GetOutputName(idx, allocator);

    Ort::TypeInfo outputTypeInfo = p_session.GetOutputTypeInfo(idx);

    auto TypeAndShape = outputTypeInfo.GetTensorTypeAndShapeInfo();

    //ONNXTensorElementDataType eleType = TypeAndShape.GetElementType();
    std::vector<int64_t> tenShape = TypeAndShape.GetShape();
     
    outputDim.push_back(std::make_shared<DimensionInfomation>(outputName, tenShape));
  }


  return new Model(labels, inputDim, outputDim, blobs);
}


std::vector<std::string> Resources::ModelLoader::ParseClassNames(const Ort::Session& p_session)
{
  std::vector<std::string> result;  
  Ort::AllocatorWithDefaultOptions allocator;
  Ort::ModelMetadata metadata = p_session.GetModelMetadata();
  std::vector<Ort::AllocatedStringPtr> keys = 
    metadata.GetCustomMetadataMapKeysAllocated(allocator); 
  const std::string keyName = "names";
  bool availableLabels = false; 

  for(const auto& key: keys) { 
    if(0 == keyName.compare(key.get())) 
      availableLabels = true;
  }

  if(availableLabels) {
    Ort::AllocatedStringPtr namesMetaData =
      metadata.LookupCustomMetadataMapAllocated(keyName.c_str(), allocator);

    size_t idx = 0;
    bool started = false;
    std::string str = std::string(namesMetaData.get());
    for(auto iter = str.begin(); iter != str.end();) {
      if(started) {
        if(*(iter+idx) == '\'') {
          result.push_back(std::string(iter, iter+idx));
          iter += ++idx;
          idx = 0;
          started = false;
        }else
          idx++;
      }
      else {
        if(*iter == '\'')
          started = true; 
        iter++;
      }     
    }
  } 
  return result;
}

