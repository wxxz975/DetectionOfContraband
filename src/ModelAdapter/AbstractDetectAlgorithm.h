#pragma once
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <opencv2/opencv.hpp>


typedef struct _DetectionResultNode
{
    cv::Rect box;
    int classIndex;
    float confidence;
}DetectionResultNode, *pDetectionResultNode;

class AbstractDetectAlgorithm
{
public:
    std::vector<std::string> m_labelNames; 
    float confThreshold = 0.4; // confidence threshold
    float iouThreshold = 0.45;  // iou threshold
public:

    AbstractDetectAlgorithm() = default;

    virtual ~AbstractDetectAlgorithm() = default;

    virtual const std::vector<DetectionResultNode> detect(const cv::Mat& image) = 0;
    
    virtual bool reloadModel(const std::string& modelPath, const bool isGPU = true) = 0; 
};


