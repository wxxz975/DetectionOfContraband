#pragma once


namespace DcUI::Types
{
  /*
   * store rgba in default mode
   * */
  struct Color
  {
    Color(float p_r = 1.0f, float p_g = 1.0f, float p_b = 1.0f, float p_a = 1.0f);
    
    //Color(float p_r = 1.0f, float p_g = 1.0f, float p_b = 1.0f);

    float r, g, b ,a;
    
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color While;
    static const Color Black;
    static const Color Grey;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Magenta;
    
    /*
     * Compares two colors, return true if they are identical
     * */
    bool operator==(const Color& p_other);

    /*
     * Compares two colors, return true if they are different 
     * */
    bool operator!=(const Color& p_other);

  };

}
