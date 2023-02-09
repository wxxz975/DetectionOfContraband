#include <core/session/onnxruntime_cxx_api.h>

class TensorHelper
{   
public:
    TensorHelper(/* args */) = default;
    ~TensorHelper() = default;

    // Tensors to be created are all of the same type
    template<typename T>
    std::vector<Ort::Value> CreateTensor(std::vector<std::vector<T> >& Values, 
                                    const std::vector<std::vector<int64_t> >& TensorShape,
                                    const Ort::MemoryInfo memoryInfo) { 
        std::vector<Ort::Value> newTensor;
        size_t Len = Values.size();

        if(Values.empty()) 
            return newTensor;
        
        for(size_t idx = 0; idx < Len; ++idx) {
            newTensor.push_back(
                Ort::Value::CreateTensor<T>(
                    memoryInfo, Values[idx].data(), Values[idx].size(),
                    TensorShape[idx].data(), TensorShape[idx].size()
                ));    
        }

        return newTensor;
    }

    // Tensors to be created may not be the same type
    template<typename T>
    std::vector<Ort::Value> CreateTensor(std::vector<std::vector<T>>& Values, 
                                    const std::vector<std::vector<int64_t>>& TensorShape,
                                    const Ort::MemoryInfo& memoryInfo,
                                    const std::vector<ONNXTensorElementDataType>& eleType) {
        std::vector<Ort::Value> newTensor;
        size_t Len = Values.size();

        if(Values.empty()) 
            return newTensor;

        for(size_t idx = 0; idx < Len; ++idx) {
            Ort::Value value;
            switch (eleType) {
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT: {
                    value = Ort::Value::CreateTensor<float>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8: {
                    value = Ort::Value::CreateTensor<uint8_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8: {
                    value = Ort::Value::CreateTensor<int8_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16: {
                    value = Ort::Value::CreateTensor<uint16_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16: {
                    value = Ort::Value::CreateTensor<int16_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32: {
                    value = Ort::Value::CreateTensor<int32_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64: {
                    value = Ort::Value::CreateTensor<int64_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_BOOL: {
                    value = Ort::Value::CreateTensor<bool>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16: {
                    value = Ort::Value::CreateTensor(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size(),
                        ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_DOUBLE: {
                    value = Ort::Value::CreateTensor<double>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT32: {
                    value = Ort::Value::CreateTensor<uint32_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                case ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT64: {
                    value = Ort::Value::CreateTensor<uint64_t>(
                        memoryInfo, Values[idx].data(), Values[idx].size(),
                        TensorShape[idx].data(), TensorShape[idx].size()
                    );
                    break;
                }
                default:
                    break;
            }
            newTensor.push_back(value);    
        }
    }


    template<typename T>
    std::vector<const T*> GetOutput(std::vector<Ort::Value>& outputTensors) {
        std::vector<const T*> result;
        for (const auto tensor: outputTensors) {
            const auto tensorPtr = tensor.GetTensorData<T>();
            result.push_back(tensorPtr);
        }
        return result;
    }

    


};
