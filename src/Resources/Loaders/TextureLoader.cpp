#include "Resources/Loaders/TextureLoader.h"
#include "stb/stb_image.h"
#include <GL/gl.h>



Texture* TextureLoader::CreateFromFile(const std::string& p_filepath, 
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter)
{
  GLuint textureID;
  int textureWidth;
  int textureHeight;
  int bitsPerPixel;
  glGenTextures(1, &textureID);
  
  stbi_set_flip_vertically_on_load(true);
  unsigned char* dataBuffer = stbi_load(p_filepath.c_str(), &textureWidth, &textureHeight, 
      &bitsPerPixel, 4);

  if(dataBuffer)
  {
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, dataBuffer);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(p_firstFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(p_secondFilter));
  
    stbi_image_free(dataBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return new Texture(p_filepath, textureID, textureWidth, textureHeight,
        p_firstFilter, p_secondFilter);
  }
  else
  {
    stbi_image_free(dataBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    return nullptr;
  }
}

Texture* TextureLoader::CreateFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter)
{
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, p_width, p_height, 0, GL_RGBA, 
      GL_UNSIGNED_BYTE, p_data);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  return new Texture("", textureID, 1, 1, p_firstFilter, p_secondFilter);
}

void TextureLoader::Reload(Texture& p_texture, const std::string& p_filepath,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter)
{
  Texture* newTexture = CreateFromFile(p_filepath.c_str(), p_firstFilter, p_secondFilter);

  if(newTexture)
  {
    *const_cast<uint32_t*>(&p_texture.id) = newTexture->id; 
    *const_cast<uint32_t*>(&p_texture.width) = newTexture->width;
    *const_cast<uint32_t*>(&p_texture.height) = newTexture->height;
    //*const_cast<uint32_t*>(&p_texture.bitsPerPixel) = newTexture->bitsPerPixel;
    *const_cast<TextureFilteringMode*>(&p_texture.firstFilter) = newTexture->firstFilter;
    *const_cast<TextureFilteringMode*>(&p_texture.secondFilter) = newTexture->secondFilter;

    delete newTexture;
  }
}


bool TextureLoader::Destory(Texture*& p_textureInstance)
{
  if(p_textureInstance)
  {
    glDeleteTextures(1, &p_textureInstance->id);
    delete p_textureInstance;
    p_textureInstance = nullptr;

    return true;
  }

  return false;
}
