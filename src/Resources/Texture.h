#pragma once 
#include <stdint.h>
#include <string>
#include "Loaders/TextureFilteringMode.h"
#include "Resources/Loaders/TextureLoader.h"

namespace Resources
{
  class Texture
  {
    friend class Resources::Loaders::TextureLoader;
    public:
    /*
     * Bind the texture to the given slot
     *  @param p_slot
     * */  
    void Bind(uint32_t p_slot = 0) const;

    /*
     * Unbind the texture
     * */
    void Unbind() const;


    private:
      Texture(const std::string& p_path, uint32_t p_id, 
        uint32_t p_width, uint32_t p_height,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter);
    ~Texture() = default;

    public:
      const uint32_t id;
      const uint32_t width;
      const uint32_t height;
    //const uint32_t bitsPerPixel;
      const std::string path;
      const TextureFilteringMode firstFilter;
      const TextureFilteringMode secondFilter;
  };
}
