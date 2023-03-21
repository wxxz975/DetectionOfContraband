#include "OnnxModelAdapter/Yolov5/Postprocessing.h"



std::vector<ResultNode> OnnxModelAdapter::Yolov5::Postprocessing::Impl(Ort::Value& outputTensor, 
          const cv::Size& resizedImageShape,const cv::Size& originalImageShape,
          const float& confThreshold, const float& iouThreshold) 
{  
    std::vector<cv::Rect> boxes;
    std::vector<float> confs;
    std::vector<int> classIds;

    auto* rawOutput = outputTensor.GetTensorData<float>();
    std::vector<int64_t> outputShape = outputTensor.GetTensorTypeAndShapeInfo().GetShape();
    size_t count = outputTensor.GetTensorTypeAndShapeInfo().GetElementCount();
     
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

    std::vector<ResultNode> detections;

    for (int idx : indices) {
        ResultNode det;
        det.box = cv::Rect(boxes[idx]);
        GetOriCoords(resizedImageShape, originalImageShape, det.box);

        det.confidence = confs[idx];
        det.classIndex = classIds[idx];
        detections.emplace_back(det);
    }

    return detections;
}



void OnnxModelAdapter::Yolov5::Postprocessing::GetBestClassInfo(std::vector<float>::iterator it, 
    const int& numClasses, float& bestConf, int& bestClassId)
{
  // first 5 element are box and obj confidence
  bestClassId = 5;
  bestConf = 0;
  const int otherCnt = 5; // skip x, y, w, h, box_conf

  for (int i = otherCnt; i < numClasses + otherCnt; i++)
  {
    if (it[i] > bestConf)
    {
      bestConf = it[i];
      bestClassId = i - otherCnt;
    }
  }
}
void OnnxModelAdapter::Yolov5::Postprocessing::GetOriCoords(const cv::Size& currentShape, 
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


