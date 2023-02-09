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
protected:
    std::vector<std::string> m_labelNames;
public:

    AbstractDetectAlgorithm() = default;

    virtual ~AbstractDetectAlgorithm() = default;

    virtual const std::vector<DetectionResultNode> detect(const cv::Mat& image) = 0;
};


