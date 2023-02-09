#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace OnnxruntimeUtils {

    // to parse the raw data where readed from onnx model. format:  names = ['car', 'people', 'house', ...]
    std::vector<std::string> parseVecFromRaw(const std::string& rawData);   

    size_t vectorProduct(const std::vector<int64_t>& vector);

    
    void letterbox(const cv::Mat& image, cv::Mat& outImage,
                   const cv::Size& newShape,
                   const cv::Scalar& color,
                   bool auto_,
                   bool scaleFill,
                   bool scaleUp,
                   int stride);

    void scaleCoords(const cv::Size& imageShape, cv::Rect& coords, const cv::Size& imageOriginalShape);

    void getBestClassInfo(std::vector<float>::iterator it, const int& numClasses,
                                    float& bestConf, int& bestClassId);    

    void visualizeDetection(cv::Mat& image, std::vector<Detection>& detections,
                               const std::vector<std::string>& classNames);          
}