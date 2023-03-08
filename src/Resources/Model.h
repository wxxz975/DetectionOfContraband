#pragma once 
#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include <core/session/onnxruntime_cxx_api.h>

/*
 *  TODO: split the class task
 * */
namespace Resources
{
  class Model
  {
    friend class ModelLoader;

    public:
      //                   < DimensionName, DimensionShape>
      using  OneDimension = std::pair<std::string, std::vector<int64_t>>;

      //          <input/outputDataPointer, SizeOfBlob>
      template<typename T>
      using Blob = std::pair<std::shared_ptr<T[]>, size_t>; 

      typedef std::vector<Blob<float>> Blobs;


    public:

      /*
      * Return the model`s label
      * */
      const std::vector<std::string>& GetClassNames() const;


      /*
      * Return the model`s input dimemsion
      * */
      const std::vector<OneDimension>& GetInputDimenssion() const; 
     
      /*
       * Return the model`s output dimenssion
       * */ 
      const std::vector<OneDimension>& GetOutputDimenssion() const;

    private:
      Model(const std::string& p_modelpath);
      ~Model() = default;

    public:
      // model path
      const std::string modelPath;
    private:
      
      std::vector<std::string> m_classNames;

      std::vector<OneDimension> m_inputDim;
      std::vector<OneDimension> m_outputDim;


      bool isDynamicInputShape = false;

      // default using float type
      Blobs blobs;

  };
}
