#pragma once
#include <string>
#include <vector>
#include <memory>
#include <core/session/onnxruntime_cxx_api.h>
#include "OnnxModelAdapter/AbstractDetectAlgorithm.h"
#include "OnnxruntimeAssets.h"

class OnnxruntimeInfer: public OnnxruntimeAssets,
                    public AbstractDetectAlgorithm
{
private:
    void preprocessing(const cv::Mat &image, std::vector<int64_t>& inputTensorShape);
    const std::vector<DetectionResultNode> postprocessing(const cv::Size& resizedImageShape,
                                                    const cv::Size& originalImageShape,
                                                    Ort::Value& outputTensors,
                                                    const float& confThreshold, const float& iouThreshold);
    bool loadModel(const std::string& modelPath);

    bool initLabels();
    bool initTensor();
    bool initEnv(const std::string& modelPath);
    
public:
    OnnxruntimeInfer() = default;
    OnnxruntimeInfer(const std::string& modelPath = "x_ray.onnx", const bool isGPU = true);
    ~OnnxruntimeInfer();

    virtual bool reloadModel(const std::string& modelPath, const bool isGPU = true) override;
    
    virtual const std::vector<DetectionResultNode> detect(const cv::Mat &image) override; 
};
