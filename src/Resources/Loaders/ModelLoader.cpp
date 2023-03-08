#include "Resources/Loaders/ModelLoader.h"


Resources::Model* Resources::Loaders::ModelLoader::LoadModel(const std::string& p_modelPath)
{
  Resources::Model *mod = new Resources::Model(p_modelPath);

}


std::vector<std::string> ParseClassNames(Ort::Session p_session)
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

