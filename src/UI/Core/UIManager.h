#pragma once 
#include <string>
#include <unordered_map>
#include <imgui/imgui_impl_glfw.h>
#include "UI/Style/Styling/StyleManager.h"
#include "UI/Style/UIFont/FontManager.h"


namespace DcUI::Core
{

  class UIManager
  {
    public:
      /*
       * Create the UI manager. will setup ImGui internally\
       * @param p_glfwWindow
       * @param p_style
       * @param p_glslVersion (#version 150)
       * */
      UIManager( GLFWwindow* p_glfwWinow, 
          DcUI::Style::Styling::EStyle p_style = 
          DcUI::Style::Styling::EStyle::IM_DARK_STYLE, 
          const std::string& p_glslVersion = "#version 130");

      /*
       * Destory the UI manager. will handle ImGui destruction.
       * */
      ~UIManager();

      /*
       * Enable the docking system
       * @param p_value
       * */

      void EnableDocking(bool p_value);

      /*
       * Apply a new style to the UI elements
       * */
      void ApplyStyle(Style::Styling::EStyle p_style);

      
      /*
       * Get the Font Manager. this can change the default font.
       * */
      Style::FontManager& GetFontManager();

      

      /*
       * Defines the canvas to use
       * @param p_canvas
       * */
       void SetCanvas();



    private:
      Style::StyleManager m_styleMgr;
      Style::FontManager m_fontMgr;
      
      std::string m_layoutSaveFilename = "imgui.ini";

     // TODO:canvas 
  };


}
