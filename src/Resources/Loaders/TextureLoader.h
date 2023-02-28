#pragma once
#include <string>
#include "Resources/Texture.h"

class TextureLoader
{
  public:
    /*
     *  Disable constructor
     * */
    TextureLoader() = delete;

    /*
     * Create a Texture from file
     * */
    static Texture* CreateFromFile(const std::string& p_filepath, 
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter);
    
    /*
     * Create a texture from memory
     * */
    static Texture* CreateFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter);

    /*
     *  Reload a texture from file
     * */
    static void Reload(Texture& p_texture, const std::string& p_filepath,
        TextureFilteringMode p_firstFilter, TextureFilteringMode p_secondFilter);

    /*
     * Destory a texture
     * */ 
    static bool Destory(Texture*& p_textureInstance);

};

