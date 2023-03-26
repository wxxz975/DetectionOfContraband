#pragma once
#include <stdint.h>

namespace DcUI::Internal
{

  /*
   * sample union necessary for imgui textureID
   * */
  union TextureID
  {
    uint32_t id;
    void* raw;
  };

}
