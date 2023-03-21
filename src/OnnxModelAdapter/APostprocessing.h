#pragma once
#include <vector>
#include <core/session/onnxruntime_cxx_api.h>
#include "OnnxModelAdapter/OnnxCommon.hpp"



namespace OnnxModelAdapter
{
  /*
   * provide a common interface for upper layer, 
   * and the specific implementation is determined based on the algorithm used
   * */
  class APostprocessing
  {
    public:
      APostprocessing() = default;
      virtual ~APostprocessing() = 0;

    public:

      virtual std::vector<ResultNode> Impl(Ort::Value& outputTensor, 
          const cv::Size& resizedImageShape,const cv::Size& originalImageShape,
          const float& confThreshold, const float& iouThreshold);


  };
}
