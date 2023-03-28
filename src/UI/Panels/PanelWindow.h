#pragma once
#include <string>
#include <memory>
#include "Common/Eventing/Event.h"
#include "Common/Math/Vector.h"
#include "UI/Panels/APanelTransformable.h"
#include "UI/Settings/PanelWindowSettings.h"

namespace DcUI::Panels
{
  
  typedef Common::Math::FVector2 FVector2;

  class PanelWindow: public APanelTransformable
  {
    public:
      PanelWindow(const std::string& p_name = "", bool p_open = true, 
          const Settings::PanelWindowSettings& p_panelSettings = Settings::PanelWindowSettings{});

      void Open();

      void Close();

      void Focus();

      void SetOpened(bool p_opened);

      bool IsOpened() const;

      bool IsHovered() const;

      bool IsFocused() const;

      bool IsAppearing() const;

      void ScrollToBotton();

      void ScrollToTop();
      
      bool IsScrollToBotton() const;

      bool IsScrollToTop() const;

    protected:
      virtual void _Draw_Impl() override;


    public:
      std::string name;
      
      FVector2 minSize = {0.f, 0.f};
      FVector2 maxSize = {0.f, 0.f};

      bool resizable = true;
      bool closable = false;
      bool movable = true;
      bool scrollable = true;
      bool dockable = false;
      bool hideBackground = false;
      bool horizontalScrollbar = false;
      bool forceHorizontalScrollbar = false;
      bool forceVerticalScrollbar = false;
      bool allowHorizontalScrollbar = false;
      bool bringToFrontOnFocus = true;
      bool collapsable = false;
      bool allowInputs = true;
      bool titleBar = true;

      Common::Eventing::Event<> OpenEvent;
      Common::Eventing::Event<> CloseEvent;

    private:
      bool m_opened;
      bool m_hovered;
      bool m_focused;
      bool m_mustScrollToBotton = false;
      bool m_mustScrollToTop = false;
      bool m_scrollToBotton = false;
      bool m_scrollToTop = false;


  };
}
