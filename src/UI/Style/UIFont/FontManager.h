#pragma once
#include <string>
#include <unordered_map>
#include <imgui/imgui.h>


namespace DcUI::Style
{


  class FontManager
  {
    public:
      FontManager();
      ~FontManager();

      bool LoadFont(const std::string& p_id, const std::string& p_path, float p_fontSize);

      bool UnloadFont(const std::string& p_id);

      bool UseFont(const std::string& p_id);
    private:
      std::unordered_map<std::string, ImFont*> m_fonts;    

  };
}
