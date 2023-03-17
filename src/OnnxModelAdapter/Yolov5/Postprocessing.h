#include <opencv2/opencv.hpp>
#include <vector>
#include <core/session/onnxruntime_cxx_api.h>
/*
 * struct 
 * {
 *   float cx, cy, w, h;
 *   float confidence;
 *   float classConfidence[classNumber];
 * }
 * the structure size depend on the size of classNumber
 * */

// get the coordinates in the original image
void GetOriCoords(const cv::Size& currentShape, 
    const cv::Size& originalShape, cv::Rect& outCoords)
{
  float gain = std::min((float)currentShape.height / (float)originalShape.height,
                        (float)currentShape.width / (float)originalShape.width);

  int pad[2] = {
    (int) (((float)currentShape.width - (float)originalShape.width * gain) / 2.0f),
    (int) (((float)currentShape.height - (float)originalShape.height * gain) / 2.0f)
  };

  outCoords.x = (int) std::round(((float)(outCoords.x - pad[0]) / gain));
  outCoords.y = (int) std::round(((float)(outCoords.y - pad[1]) / gain));

  outCoords.width = (int) std::round(((float)outCoords.width / gain));
  outCoords.height = (int) std::round(((float)outCoords.height / gain));

}

void GetBestClassInfo(std::vector<float>::iterator it, const int& numClasses,
                                    float& bestConf, int& bestClassId) {
    // first 5 element are box and obj confidence
    bestClassId = 5;
    bestConf = 0;

    for (int i = 5; i < numClasses + 5; i++)
    {
        if (it[i] > bestConf)
        {
            bestConf = it[i];
            bestClassId = i - 5;
        }
    }

}

struct DetectionResultNode
{

};
struct SInputTensor
{
  int64_t batch;
  int64_t channels;
  int64_t width;
  int64_t height;
};

struct SOutputTensor
{
  int64_t batch;
  int64_t features;
  int64_t attr;   // include[cx, cy, w, h, boxConf] + [obj1Conf, obj2Conf, obj3Conf...]
};
const std::vector<DetectionResultNode> postprocessing(const cv::Size& resizedImageShape,
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
     
    // this will copy rawOutput memory to output
    std::vector<float> output(rawOutput, rawOutput + count);


    // first 5 elements are box[4] and obj confidence
    int numClasses = (int)outputShape[2] - 5;
    int elementsInBatch = (int)(outputShape[1] * outputShape[2]);
    // 它相当于只有一个batch, 这里取的ouput的withd*height


    for (auto it = output.begin(); 
        it != output.begin() + elementsInBatch; 
        it += outputShape[2])
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
            GetBestClassInfo(it, numClasses, objConf, classId);

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
        scaleCoords(resizedImageShape, det.box, originalImageShape);

        det.confidence = confs[idx];
        det.classIndex = classIds[idx];
        detections.emplace_back(det);
    }

    return detections;
}


