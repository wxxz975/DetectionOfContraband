#pragma once

#include <string>
#include <unordered_map>

#include "UI/Modules/Canvas.h"
#include "UI/Panels/APanel.h"
#include "UI/Panels/PanelWindow.h"


namespace Core
{
  class PanelsManager
  {
    public:
      /*
       * Constructor
       * @param: p_canvas
       * */
      PanelsManager(DcUI::Modules::Canvas& p_canvas);
      ~PanelsManager() = default;
  
      
      template<typename T, typename... Args>
      void CreatePanel(const std::string& p_id, Args&&... p_args)
      {
        if constexpr(std::is_base_of<DcUI::Panels::PanelWindow, T>::value)
        {
          m_panels.emplace(p_id, std::make_unique<T>(m_canvas, std::forward<Args>(p_args)...));
          T& instance = *static_cast<T*>(m_panels.at(p_id).get());
          //GetPanelAs<>(const std::string &p_id)
           
        }
        else
        {
          m_panels.emplace(p_id, std::make_unique<T>(std::forward<Args>(p_args)...));
        }

        m_canvas.AddPanel(*m_panels.at(p_id).get());
      }

      template <typename T>
      T& GetPanelAs(const std::string& p_id)
      {
        return *static_cast<T*>(m_panels.at(p_id).get());
      }
      
    private:
      DcUI::Modules::Canvas& m_canvas;
      std::unordered_map<std::string, std::unique_ptr<DcUI::Panels::APanel>> m_panels;
  };
}
