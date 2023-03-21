#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "OnnxModelAdapter/AbstractDetectAlgorithm.h"

namespace OnnxruntimeUtils {

    void visualizeDetection(cv::Mat& image, std::vector<DetectionResultNode>& detections,
                               const std::vector<std::string>& classNames);          
}
