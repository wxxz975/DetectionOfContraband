#pragma once
#include <vector>
#include <opencv2/opencv.hpp>


namespace OnnxModelAdapter
{
  /*
   *  abstract the preprocess, because different models may treat the output differently
   * */ 
  class APreprocessing
  {
    public:
      APreprocessing() = default;
      virtual ~APreprocessing() = 0;

    public:
      virtual void Impl(const cv::Mat &image, const std::vector<int64_t>& inputTensorShape, float* outBlob) = 0;  

      /*
       *
       * */
  };

}
