#include "Resources/Model.h"


const std::vector<std::string>& Resources::Model::GetClassNames() const
{
  return m_classNames;
}

const std::vector<Resources::Model::OneDimension>& Resources::Model::GetInputDimenssion() 
  const
{
  return m_inputDim;
}

const std::vector<Resources::Model::OneDimension>& Resources::Model::GetOutputDimenssion() 
  const 
{
  return m_outputDim; 
}

Resources::Model::Model(std::vector<std::string> p_classNames, 
    std::vector<OneDimension> p_inputDim, 
    std::vector<OneDimension> p_outputDim, Blobs p_blobs):
  m_classNames(p_classNames), m_inputDim(p_inputDim), m_outputDim(p_outputDim), 
  m_blobs(p_blobs) 
{

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
