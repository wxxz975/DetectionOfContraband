#include <opencv2/opencv.hpp>
#include <vector>

 
/*
 * normalize image size to model`s input shape
 * @param image: which need to 
 * */
void letterbox(const cv::Mat& image, cv::Mat& outImage,
                      const cv::Size& newShape = cv::Size(640, 640),
                      const cv::Scalar& color = cv::Scalar(114, 114, 114),
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

    /* dynamic width and height
    if (auto_)
    {
        dw = (float)((int)dw % stride);
        dh = (float)((int)dh % stride);
    }
   */
    if (scaleFill)
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
    cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, 
        cv::BORDER_CONSTANT, color);
}

/* 
 * prepare for inference
 * @param image: Image to be used for model`s input
 * @param inputTensorShape: Input shape of model
 * @param outBlob: Address to copy the data to after preprocessing
 * */
void preprocessing(const cv::Mat& image, const std::vector<int64_t>& inputTensorShape, 
    float* outBlob)
{
  cv::Mat resizedImage, floatImage;
  cv::cvtColor(image, resizedImage, cv::COLOR_BGR2RGB);
  
  // the example of inputTensorShape: [1, 3, 640, 640]
  letterbox(resizedImage, resizedImage, cv::Size(inputTensorShape[2], inputTensorShape[3]),
      cv::Scalar(114, 114, 114));

  resizedImage.convertTo(floatImage, CV_32FC3, 1 / 255.0);

  cv::Size floatImageSize {floatImage.cols, floatImage.rows};

  // hwc -> chw(height width channels)
  std::vector<cv::Mat> chw(floatImage.channels());
  for (int i = 0; i < floatImage.channels(); ++i)
  {
    chw[i] = cv::Mat(floatImageSize, CV_32FC1, 
        outBlob + i * floatImageSize.width * floatImageSize.height);
  }
  cv::split(floatImage, chw);

}

