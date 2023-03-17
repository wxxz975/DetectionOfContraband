#pragma once 
#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include <core/session/onnxruntime_cxx_api.h>


/*
 *  
 * */
namespace Resources
{
  class Model
  {
    friend class ModelLoader;

    public:

    // some infomation of single dimension 
    struct DimensionInfomation
    {
      std::string dimName;
      size_t tensorSize;
      std::vector<int64_t> tensor;
      ONNXTensorElementDataType type;
    };

    using DimInfo = struct DimensionInfomation; 

    //                   < DimensionName, DimensionShape>
      using  OneDimension = DimInfo;

      //          <input/outputDataPointer, SizeOfBlob>
      template<typename T>
      using Blob = T*; 

      using Blobs = std::vector<Blob<float>>;


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

      /*
       * Return the model`s input data(blobs)
       * */
      const Blobs& GetInputPtr() const;

    private:
      Model(std::vector<std::string> p_classNames, std::vector<OneDimension> p_inputDim, 
          std::vector<OneDimension> p_outputDim, Blobs p_blobs);

      ~Model();
    public:
      // model path
      //const std::string m_pModelPath;
    private:
      
      const std::vector<std::string> m_classNames;

      const std::vector<OneDimension> m_inputDim;
      const std::vector<OneDimension> m_outputDim;

      bool isDynamicInputShape = false;
       
      // default using float type
      Blobs m_blobs;

  };
}
