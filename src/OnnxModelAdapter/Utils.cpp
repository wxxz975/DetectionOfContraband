#include "Utils.h"

std::vector<std::string> OnnxruntimeUtils::parseVecFromRaw(const std::string& rawData) {
    std::vector<std::string> ans;

    for(auto iter = rawData.cbegin(); iter < rawData.cend(); ) {
        if(*iter == '\'') {
            auto startIdx = ++iter;
            while(*iter != '\'') ++iter;
            //printf("%c\n", *iter);
            ans.push_back(std::string(startIdx, iter));
            iter++;
        }else iter++;
    }
    
    return ans;
}

size_t OnnxruntimeUtils::vectorProduct(const std::vector<int64_t>& vector)
{
    if (vector.empty())
        return 0;

    size_t product = 1;
    for (const auto& element : vector)
        product *= element;

    return product;
}

// used to resize image size
void OnnxruntimeUtils::letterbox(const cv::Mat& image, cv::Mat& outImage,
                      const cv::Size& newShape = cv::Size(640, 640),
                      const cv::Scalar& color = cv::Scalar(114, 114, 114),
                      bool auto_ = true,
                      bool scaleFill = false,
                      bool scaleUp = true,
                      int stride = 32)
{
    cv::Size shape = image.size();
    float r = std::min((float)newShape.height / (float)shape.height,
                       (float)newShape.width / (float)shape.width);
    if (!scaleUp)
        r = std::min(r, 1.0f);

    float ratio[2] {r, r};
    int newUnpad[2] {(int)std::round((float)shape.width * r),
                     (int)std::round((float)shape.height * r)};

    auto dw = (float)(newShape.width - newUnpad[0]);
    auto dh = (float)(newShape.height - newUnpad[1]);

    if (auto_)
    {
        dw = (float)((int)dw % stride);
        dh = (float)((int)dh % stride);
    }
    else if (scaleFill)
    {
        dw = 0.0f;
        dh = 0.0f;
        newUnpad[0] = newShape.width;
        newUnpad[1] = newShape.height;
        ratio[0] = (float)newShape.width / (float)shape.width;
        ratio[1] = (float)newShape.height / (float)shape.height;
    }

    dw /= 2.0f;
    dh /= 2.0f;

    if (shape.width != newUnpad[0] && shape.height != newUnpad[1])
    {
        cv::resize(image, outImage, cv::Size(newUnpad[0], newUnpad[1]));
    }

    int top = int(std::round(dh - 0.1f));
    int bottom = int(std::round(dh + 0.1f));
    int left = int(std::round(dw - 0.1f));
    int right = int(std::round(dw + 0.1f));
    cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);
}

// find the coordinates of the object in the original image
void OnnxruntimeUtils::scaleCoords(const cv::Size& imageShape, cv::Rect& coords, const cv::Size& imageOriginalShape)
{
    float gain = std::min((float)imageShape.height / (float)imageOriginalShape.height,
                          (float)imageShape.width / (float)imageOriginalShape.width);

    int pad[2] = {(int) (( (float)imageShape.width - (float)imageOriginalShape.width * gain) / 2.0f),
                  (int) (( (float)imageShape.height - (float)imageOriginalShape.height * gain) / 2.0f)};

    coords.x = (int) std::round(((float)(coords.x - pad[0]) / gain));
    coords.y = (int) std::round(((float)(coords.y - pad[1]) / gain));

    coords.width = (int) std::round(((float)coords.width / gain));
    coords.height = (int) std::round(((float)coords.height / gain));
}

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

void OnnxruntimeUtils::getBestClassInfo(std::vector<float>::iterator it, const int& numClasses,
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

void OnnxruntimeUtils::visualizeDetection(cv::Mat& image, std::vector<DetectionResultNode>& detections,
                               const std::vector<std::string>& classNames)
{
    for (const auto& detection : detections)
    {
        cv::rectangle(image, detection.box, cv::Scalar(229, 160, 21), 2);

        int x = detection.box.x;
        int y = detection.box.y;

        int conf = (int)std::round(detection.confidence * 100);
        int classId = detection.classIndex;
        std::string label = classNames[classId] + " 0." + std::to_string(conf);

        int baseline = 0;
        cv::Size size = cv::getTextSize(label, cv::FONT_ITALIC, 0.8, 2, &baseline);
        cv::rectangle(image,
                      cv::Point(x, y - 25), cv::Point(x + size.width, y),
                      cv::Scalar(229, 160, 21), -1);

        cv::putText(image, label,
                    cv::Point(x, y - 3), cv::FONT_ITALIC,
                    0.8, cv::Scalar(255, 255, 255), 2);
    }
}
