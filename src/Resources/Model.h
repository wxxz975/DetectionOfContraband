#pragma once 
#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include <core/session/onnxruntime_cxx_api.h>

/*
 *  TODO: split the class task
 * */

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

  public:
    //                   < DimensionName, DimensionShape>
    using  OneDimension = std::pair<std::string, std::vector<int64_t>>;
    
    //          <input/outputDataPointer, SizeOfBlob>
    template<typename T>
    using Blob = std::pair<std::shared_ptr<T[]>, size_t>; 

    //typedef std::pair<std::shared_ptr<>>
  private:
    std::vector<std::string> m_classNames;
   
    std::vector<OneDimension> m_inputDim;
    std::vector<OneDimension> m_outputDim;

     
    bool isDynamicInputShape = false;
 
    // default using float type
    std::vector<Blob<float>> blobs;

};

