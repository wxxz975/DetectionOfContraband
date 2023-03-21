#include <opencv2/opencv.hpp>
#include "OnnxModelAdapter/APostprocessing.h"


namespace OnnxModelAdapter::Yolov5
{
  class Postprocessing: public APostprocessing
  {
    public:
      Postprocessing() = default;
      virtual ~Postprocessing() = 0;

    public:
      virtual std::vector<ResultNode> Impl(Ort::Value& outputTensor, 
          const cv::Size& resizedImageShape,const cv::Size& originalImageShape,
          const float& confThreshold, const float& iouThreshold) override;

    private:
      void GetBestClassInfo(std::vector<float>::iterator it, const int& numClasses,
                                    float& bestConf, int& bestClassId);
      
      // get the coordinates in the original image
      void GetOriCoords(const cv::Size& currentShape, const cv::Size& originalShape, cv::Rect& outCoords);

  };

}


