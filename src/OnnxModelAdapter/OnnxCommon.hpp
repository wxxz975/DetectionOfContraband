#pragma once
#include <opencv2/opencv.hpp>



/*typedef struct*/
/*{*/
  /*float left, top, width, height;*/
  /*float conf;*/
/*}DetectionResult;*/

typedef struct _DetectionResultNode
{
    cv::Rect box;
    int classIndex;
    float confidence;
}ResultNode, *pResultNode;



