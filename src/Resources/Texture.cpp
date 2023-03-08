#include "Texture.h"
#include <GL/gl.h>

void Resources::Texture::Bind(uint32_t p_slot) const
{
  glActiveTexture(GL_TEXTURE0 + p_slot);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Resources::Texture::Unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

Resources::Texture::Texture(const std::string& p_path, uint32_t p_id, 
        uint32_t p_width, uint32_t p_height,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter):
  path(p_path), id(p_id), width(p_width), height(p_height), 
  firstFilter(p_firstFilter), secondFilter(p_secondFilter)
{

}

