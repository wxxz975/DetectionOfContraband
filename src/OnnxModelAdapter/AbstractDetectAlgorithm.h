#pragma once
#include <vector>
#include "OnnxModelAdapter/OnnxCommon.hpp"
#include "OnnxModelAdapter/APreprocessing.h"
#include "OnnxModelAdapter/APostprocessing.h"


namespace OnnxModelAdapter
{
  class AbstractDetectAlgorithm
  {
    public:
      float confThreshold = 0.4; // confidence threshold
      float iouThreshold = 0.45;  // iou threshold
    public:

      AbstractDetectAlgorithm(APreprocessing* prepro, APostprocessing* postpro)
        :m_prepro(prepro), m_postpro(postpro) {} ;

      virtual ~AbstractDetectAlgorithm() = default;

      virtual const std::vector<std::vector<ResultNode>> detect(const std::vector<cv::Mat>& images) = 0;

    protected:
      std::unique_ptr<APreprocessing> m_prepro;
      std::unique_ptr<APostprocessing> m_postpro;
  };

}
