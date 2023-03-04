
#include <core/session/onnxruntime_cxx_api.h>
#include <vector>
#include <string>

class OnnxruntimeAssets
{
public:
    std::string modelDefaultPath = "yolov5s.onnx";

    Ort::Env env{nullptr};
    std::string envDefaultName = "ONNX_DETECTION";
    Ort::SessionOptions sessionOptions{nullptr};
    Ort::Session session{nullptr};
    //Ort::MemoryInfo memoryInfo;
    Ort::AllocatorWithDefaultOptions allocator;

    int intra_op_num_threads = 5;
    bool isGPU = true;

    size_t inputCount;      //  input dimensions
    size_t outputCount;     //  output dimensions

    std::vector<const char*> inputNames;
    std::vector<const char*> outputNames;
    
    std::vector<Ort::Value> inputTensors; // place to session class
    std::vector<Ort::Value> outputTensors;
    
    std::vector<std::vector<int64_t>> inputTensorShape; // yolov5 only one input/ output
    std::vector<std::vector<int64_t>> outputTensorShape;
    std::vector<cv::Size> inputShape_cv;


    std::vector<int64_t> inputTensorSize;
    std::vector<int64_t> outputTensorSize;

    std::vector<ONNXTensorElementDataType> inputTensorType;
    std::vector<ONNXTensorElementDataType> outputTensorType;

    bool isDynamicInputShape = false;

    float *blob = nullptr;
    
    std::vector<size_t> blobsSize;
    
public:

    OnnxruntimeAssets(){};
    ~OnnxruntimeAssets(){};
};

