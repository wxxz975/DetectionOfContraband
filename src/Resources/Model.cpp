#include "Resources/Model.h"



const std::vector<std::string>& Resources::Model::GetClassNames() const
{
  return m_classNames;
}

const std::vector<Resources::Model::OneDimension>& Resources::Model::GetInputDimenssion() const
{
  return m_inputDim;
}

const std::vector<Resources::Model::OneDimension>& Resources::Model::GetOutputDimenssion() const 
{
  return m_outputDim; 
}
