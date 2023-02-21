#include "OnnxruntimeInfer.h"
#include "TensorHelper.h"
#include "Utils.h"
#include <cassert>


void OnnxruntimeInfer::preprocessing(const cv::Mat &image, std::vector<int64_t>& inputTensorShape) {
    cv::Mat resizedImage, floatImage;
    cv::cvtColor(image, resizedImage, cv::COLOR_BGR2RGB);
    OnnxruntimeUtils::letterbox(resizedImage, resizedImage, inputShape_cv[0],
                     cv::Scalar(114, 114, 114), isDynamicInputShape,
                     false, true, 32);

    inputTensorShape[2] = resizedImage.rows;
    inputTensorShape[3] = resizedImage.cols;

    resizedImage.convertTo(floatImage, CV_32FC3, 1 / 255.0);
     
    cv::Size floatImageSize {floatImage.cols, floatImage.rows};
   
    // hwc -> chw
    std::vector<cv::Mat> chw(floatImage.channels());
    for (int i = 0; i < floatImage.channels(); ++i)
    {
        chw[i] = cv::Mat(floatImageSize, CV_32FC1, blob + i * floatImageSize.width * floatImageSize.height);
    }
    cv::split(floatImage, chw);

}

const std::vector<DetectionResultNode> OnnxruntimeInfer::postprocessing(const cv::Size& resizedImageShape,
                    const cv::Size& originalImageShape,
                    Ort::Value& outputTensors,
                    const float& confThreshold, const float& iouThreshold) 
{
    std::vector<cv::Rect> boxes;
    std::vector<float> confs;
    std::vector<int> classIds;

    auto* rawOutput = outputTensors.GetTensorData<float>();
    std::vector<int64_t> outputShape = outputTensors.GetTensorTypeAndShapeInfo().GetShape();
    size_t count = outputTensors.GetTensorTypeAndShapeInfo().GetElementCount();
    std::vector<float> output(rawOutput, rawOutput + count);

    // for (const int64_t& shape : outputShape)
    //     std::cout << "Output Shape: " << shape << std::endl;

    // first 5 elements are box[4] and obj confidence
    int numClasses = (int)outputShape[2] - 5;
    int elementsInBatch = (int)(outputShape[1] * outputShape[2]); // 它相当于只有一个batch, 这里取的ouput的withd*height


    for (auto it = output.begin(); it != output.begin() + elementsInBatch; it += outputShape[2])
    {
        float clsConf = it[4];

        if (clsConf > confThreshold)
        {
            int centerX = (int) (it[0]);
            int centerY = (int) (it[1]);
            int width = (int) (it[2]);
            int height = (int) (it[3]);
            int left = centerX - width / 2;
            int top = centerY - height / 2;

            float objConf;
            int classId;
            OnnxruntimeUtils::getBestClassInfo(it, numClasses, objConf, classId);

            float confidence = clsConf * objConf;

            boxes.emplace_back(left, top, width, height);
            confs.emplace_back(confidence);
            classIds.emplace_back(classId);
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confs, confThreshold, iouThreshold, indices);
    // std::cout << "amount of NMS indices: " << indices.size() << std::endl;

    std::vector<DetectionResultNode> detections;

    for (int idx : indices) {
        DetectionResultNode det;
        det.box = cv::Rect(boxes[idx]);
        OnnxruntimeUtils::scaleCoords(resizedImageShape, det.box, originalImageShape);

        det.confidence = confs[idx];
        det.classIndex = classIds[idx];
        detections.emplace_back(det);
    }

    return detections;
}


bool OnnxruntimeInfer::loadModel(const std::string& modelPath) {
    std::cout << "[+] init model ...\n";
    assert(this->initEnv(modelPath));
    assert(this->initLabels());
    assert(this->initTensor());

    std::cout << "[+] model loaded.\n";

    return true;
}

bool OnnxruntimeInfer::initLabels() {
    // maybe not exist the names`s lable
    auto metadata = session.GetModelMetadata();
    auto namesRaw = metadata.LookupCustomMetadataMapAllocated("names", allocator);
    printf("labels:%s\n", namesRaw.get());

    try {
        m_labelNames = OnnxruntimeUtils::parseVecFromRaw(namesRaw.get());
    } catch (std::exception& err) {
        std::cout << "load labels name error:"<< err.what()
             << std::endl;
        return false;
    }

    return true;
}

bool OnnxruntimeInfer::initTensor() {
    Ort::AllocatorWithDefaultOptions allocator;

    inputCount = session.GetInputCount();
    outputCount = session.GetOutputCount();

    std::cout << "input dimension: " << inputCount << "\n";
    for(size_t idx = 0; idx < inputCount; ++idx) {
        inputNames.push_back(session.GetInputName(idx, allocator));
        Ort::TypeInfo inputTypeInfo = session.GetInputTypeInfo(idx);
        
        auto eleType = inputTypeInfo.GetTensorTypeAndShapeInfo().GetElementType();
        auto tenShape = inputTypeInfo.GetTensorTypeAndShapeInfo().GetShape();
        inputTensorType.push_back(eleType);
        inputTensorShape.push_back(tenShape);
        inputShape_cv.push_back(cv::Size2f(tenShape[2], tenShape[3])); // 
        inputTensorSize.push_back(OnnxruntimeUtils::vectorProduct(tenShape));
    }

    std::cout << "output dimension: " << outputCount << "\n";
    for(size_t idx = 0; idx < outputCount; ++idx) {
        outputNames.push_back(session.GetOutputName(idx, allocator));
        Ort::TypeInfo outputTypeInfo = session.GetOutputTypeInfo(idx);

        auto eleType = outputTypeInfo.GetTensorTypeAndShapeInfo().GetElementType();
        auto tenShape = outputTypeInfo.GetTensorTypeAndShapeInfo().GetShape();
        outputTensorType.push_back(eleType);
        outputTensorShape.push_back(tenShape);
        outputTensorSize.push_back(OnnxruntimeUtils::vectorProduct(tenShape));
    }

    // 这里是因为yolo输入维度只有1
    blob = new float[inputTensorSize[0]];

    return true;
}

bool OnnxruntimeInfer::initEnv(const std::string& modelPath) {
    env = Ort::Env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, envDefaultName.c_str());
    sessionOptions = Ort::SessionOptions();
    sessionOptions.SetIntraOpNumThreads(intra_op_num_threads);

    std::vector<std::string> availableProviders = Ort::GetAvailableProviders();
    auto cudaAvailable = std::find(availableProviders.begin(), availableProviders.end(), "CUDAExecutionProvider");
    
    OrtCUDAProviderOptions cudaOption;
    cudaOption.device_id = 0;
    cudaOption.arena_extend_strategy = 0;
    cudaOption.gpu_mem_limit = std::numeric_limits<size_t>::max();
    cudaOption.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchExhaustive;
    cudaOption.do_copy_in_default_stream = 1;

    if (isGPU && (cudaAvailable == availableProviders.end()))
    {
        std::cout << "GPU is not supported by your ONNXRuntime build. Fallback to CPU." << std::endl;
        std::cout << "Inference device: CPU" << std::endl;
    }
    else if (isGPU && (cudaAvailable != availableProviders.end()))
    {
        std::cout << "Inference device: GPU" << std::endl;
        sessionOptions.AppendExecutionProvider_CUDA(cudaOption);
    }
    else
    {
        std::cout << "Inference device: CPU" << std::endl;
    }

    std::cout << "model path:" << modelPath.c_str() << "\n";
    session = Ort::Session(env, modelPath.c_str(), sessionOptions);
    return true;
}



OnnxruntimeInfer::OnnxruntimeInfer(const std::string& modelPath, const bool _isGPU): OnnxruntimeAssets(), 
                                                                        AbstractDetectAlgorithm()
{    
    this->loadModel(modelPath);
}

OnnxruntimeInfer::~OnnxruntimeInfer() {
    //delete m_assets;
}


const std::vector<DetectionResultNode> OnnxruntimeInfer::detect(const cv::Mat& image) {
    std::vector<int64_t> inputTensorShape = this->inputTensorShape[0];
    this->preprocessing(image, inputTensorShape);

    std::vector<float> inputTensorValues(blob, blob + inputTensorSize[0]);

    std::vector<Ort::Value> inputTensors;

    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtDeviceAllocator, OrtMemType::OrtMemTypeCPUInput);
    
    
    inputTensors.push_back(Ort::Value::CreateTensor<float>(
            memoryInfo, inputTensorValues.data(), inputTensorValues.size(),
            inputTensorShape.data(), inputTensorShape.size()
    ));

   
    
    std::vector<Ort::Value> outputTensors = session.Run(Ort::RunOptions{nullptr},
                                                               inputNames.data(),
                                                               inputTensors.data(),
                                                               inputTensors.size(),
                                                               outputNames.data(),
                                                               outputNames.size());
                                                      
    
   
    cv::Size resizedShape = cv::Size((int)inputTensorShape[3], (int)inputTensorShape[2]);
    auto result = this->postprocessing(resizedShape,
                                                image.size(),
                                                outputTensors[0],
                                                confThreshold, iouThreshold);
   
    
    //delete blob;

    return result;

}