#pragma once
#include "OnnxModelAdapter/AbstractDetectAlgorithm.h"
#include "OnnxModelAdapter/Yolov5/Preprocessing.h"
#include "OnnxModelAdapter/Yolov5/Postprocessing.h"
#include "Resources/Session.h"

namespace OnnxModelAdapter
{

  /*
   *  Model inference interface 
   * */
  class OnnxAlgorithm: public AbstractDetectAlgorithm
  {
    public:
      OnnxAlgorithm(): 
        AbstractDetectAlgorithm(new Yolov5::Preprocessing(), new Yolov5::Postprocessing()) {};
      ~OnnxAlgorithm();
   

    public:
      const std::vector<std::vector<ResultNode>> detect(const std::vector<cv::Mat> &images) override;
    
      bool InitModel(const std::string& p_modelPath);

    private:
      const float confThreshold = 0.5;
      const float iouThreshold = 0.5;
      std::unique_ptr<Resources::Session> m_pSession;
  };

}
