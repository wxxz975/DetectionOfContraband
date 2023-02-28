#pragma once 
#include <vector>
#include <string>
#include <stdint.h>

class Model
{
  friend class ModelLoader;
  
  public:
    
  /*
   * Return the class names
   * */
  const std::vector<std::string>& GetClassNames() const;
 

  /*
   * Return the model`s dimemsion
   * */
  const std::vector<std::vector<int64_t>>& GetDimenssion() const; 


  private:
    Model(const std::string& p_modelpath);
    ~Model();

  public:
    const std::string path;

  private:
    std::vector<std::string> m_classNames;
    std::vector<std::vector<int64_t>> m_dimenssion;
    
};

