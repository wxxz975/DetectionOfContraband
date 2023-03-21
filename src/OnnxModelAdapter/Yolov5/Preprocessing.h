#include <opencv2/opencv.hpp>
#include <vector>
#include "OnnxModelAdapter/APreprocessing.h"


namespace OnnxModelAdapter::Yolov5
{
  class Preprocessing: public APreprocessing
  {
    public:
      Preprocessing() = default;
      ~Preprocessing() = default;
    public:
      
      /*
       * initialize the image and copy the result data to outBlob
       * */
      virtual void Impl(const cv::Mat &image, 
          const std::vector<int64_t>& inputTensorShape, float* outBlob) override;
    
    private:
      /*
       * normalize image size to model`s input shape
       * @param image: which need to 
       * */
      void letterbox(const cv::Mat& image, cv::Mat& outImage, const cv::Size& newShape = cv::Size(640, 640), 
          const cv::Scalar& color = cv::Scalar(114, 114, 114), bool scaleFill = false, bool scaleUp = true,
          int stride = 32);



  };
}
 



