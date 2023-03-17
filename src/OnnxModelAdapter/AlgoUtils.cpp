#include "OnnxModelAdapter/AlgoUtils.h"
#include <vector>
#include <map>
#include <algorithm>

#include <string.h>
#define kMaxNumOutputBbox 1000

// bounding box
struct alignas(float) Bbox
{
  float x;
  float y;
  float width;
  float height;
  float score; // score
};


// intersection of union
float IoU(const Bbox& lbox, const Bbox& rbox) {
  Bbox interBox = {
    (std::max)(lbox.x - lbox.width / 2.f , rbox.x - rbox.width / 2.f), //left
    (std::min)(lbox.x + lbox.width / 2.f , rbox.x + rbox.width / 2.f), //right
    (std::max)(lbox.y - lbox.height / 2.f , rbox.y - rbox.height / 2.f), //top
    (std::min)(lbox.y + lbox.height / 2.f , rbox.y + rbox.height / 2.f), //bottom
    0 // pading, no sense
  };

  if (interBox.width > interBox.height || interBox.x > interBox.y)
    return 0.0f;

  float interBoxS = (interBox.y - interBox.x) * (interBox.height - interBox.width);
  return interBoxS / (lbox.width * lbox.height + rbox.width * rbox.height - interBoxS);
}

static inline bool cmp(const Bbox& a, const Bbox& b)
{
  return a.score > b.score;
}


void NMS(const std::vector<Bbox>& boxes, float thresh)
{
  std::sort(boxes.begin(), boxes.end(), cmp);
  for(size_t idx = 0; idx < boxes.size(); ++idx)
  {
    auto &box = boxes[idx];

  }
}


