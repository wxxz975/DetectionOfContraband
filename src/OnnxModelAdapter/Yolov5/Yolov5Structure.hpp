#include <stdint.h>
/* 
    [1*25200*85]
    batch*(channel)*struct
    
    batch = 1
    channel = [20*20*3] + [40*40*3] + [80*80*3] = 1200 + 4800 + 19200 = 25200 (fixed)
    struct = coordinate + confidence + class_confidence
    
*/
#define YOLOV5_THIRD_DIM_SIZE 5 // 1*25200*85 的第三维度大小 


// this structure must be place in infer moel, because model may different with yolov5
namespace Yolvo5RawPtr {


    template<typename T>
    struct __attribute__((packed)) Yolov5RawOuputStructure
    {
        // central x, central y, width, height
        T cx, cy, w, h;
        T box_confidence;
        T class_conf[YOLOV5_THIRD_DIM_SIZE]; 
        // 输出的大小和训练的模型类别相关 = 类别数量 + 5(1*25200*85)
    };

    using fYolov5Ptr = Yolov5RawOuputStructure<float>*;

    using f16Yolov5Ptr = Yolov5RawOuputStructure<uint16_t>*;

    using u8Yolov5Ptr = Yolov5RawOuputStructure<uint8_t>*;


}

