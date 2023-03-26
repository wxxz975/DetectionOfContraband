#include "Resources/Model.h"


Resources::Model::Model(std::vector<std::string> p_classNames, 
    std::vector<OneDimension> p_inputDim, 
    std::vector<OneDimension> p_outputDim, Blobs p_blobs):
  m_classNames(p_classNames), m_inputDim(p_inputDim), m_outputDim(p_outputDim), 
  m_blobs(p_blobs) 
{
  for(const auto& dim : p_inputDim)
    m_pInputNames.push_back(dim->Name.data());

  for(const auto& dim : p_outputDim)
    m_pOutputNames.push_back(dim->Name.data());
}

Resources::Model::~Model()
{
  for(auto& it : m_blobs) {
    if(it != nullptr){
      delete it;
      it = nullptr;
    }
  }
}
