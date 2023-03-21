#pragma once 
#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include <core/session/onnxruntime_cxx_api.h>
#include "Resources/DimensionInfomation.h"
/*
 *  
 * */
namespace Resources
{
  class Model
  {
    friend class ModelLoader;

    public:

    using  OneDimension = std::shared_ptr<DimensionInfomation>;

      //          <input/outputDataPointer, SizeOfBlob>
    template<typename T>
      using Blob = T*; 

    using Blobs = std::vector<Blob<float>>;


    public:

      /*
      * Return the model`s label
      * */
      inline const std::vector<std::string>& GetClassNames() const {
        return this->m_classNames;
      };


      /*
      * Return the model`s input dimemsion
      * */
      inline const std::vector<OneDimension>& GetInputDimenssion() const {
        return this->m_outputDim;
      }; 
     
      /*
       * Return the model`s output dimenssion
       * */ 
      //inline const std::vector<OneDimension>& GetOutputDimenssion() const {};

      /*
       * Return the model`s input data(blobs)
       * */
      inline const Blobs& GetInputPtr() const {
        return this->m_blobs;
      };

    private:
      Model(std::vector<std::string> p_classNames, std::vector<OneDimension> p_inputDim, 
          std::vector<OneDimension> p_outputDim, Blobs p_blobs);

      ~Model();
    private:
      
      const std::vector<std::string> m_classNames;

      const std::vector<OneDimension> m_inputDim;
      const std::vector<OneDimension> m_outputDim; // this maybe useless
 
      // default using float type
      Blobs m_blobs;

  };
}
