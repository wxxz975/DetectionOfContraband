#include "FontManager.h"

bool FontManager::LoadFont(const std::string& p_id, 
    const std::string& p_path, 
    float p_fontSize)
{
  if(m_fonts.find(p_id) == m_fonts.end())
  {
    auto& io = ImGui::GetIO();
    ImFont* fontInstance = io.Fonts->AddFontFromFileTTF(p_path.c_str(), p_fontSize);

    if(fontInstance) 
    {
      m_fonts[p_id] = fontInstance;
      return true;
    }
  }
  
  return false;
}

bool FontManager::UnloadFont(const std::string& p_id)
{
  if(m_fonts.find(p_id) != m_fonts.end())
  {
    m_fonts.erase(p_id);
    return true;
  }

  return false;
}

bool FontManager::UseFont(const std::string& p_id)
{
  auto foundFont = m_fonts.find(p_id);

  if(foundFont != m_fonts.end())
  {
    ImGui::GetIO().FontDefault = foundFont->second;
    return true;
  }
  return false;
}

