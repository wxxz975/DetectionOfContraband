#pragma once 

#include <memory>
#include <vector>

#include "Common/Math/Vector.h"
#include "Common/Eventing/Event.h"

#include "UI/Panels/APanel.h"
#include  "UI/Settings/Alignment.h"

namespace DcUI::Panels
{
  
  typedef Common::Math::FVector2 FVector2;

  class APanelTransformable : public APanel
  {
    public:
      APanelTransformable(
          FVector2 p_defaultPosition = {-1.f, -1.f},
          FVector2 p_defaultSize = {-1.f, -1.f},
          Settings::EHorizontalAlignment p_defaultHorizontalAlignment = Settings::EHorizontalAlignment::LEFT,
          Settings::EVerticalAlignment p_defaultVerticalAlignment = Settings::EVerticalAlignment::TOP,
          bool p_ignoreConfigFile = false
          );


      void SetPosition(const FVector2& p_position);
      
      void SetSize(const FVector2& p_size);

      void SetAlignment(Settings::EHorizontalAlignment p_horizontalAlignment, 
          Settings::EVerticalAlignment p_verticalAlignment);

      const FVector2& GetPosition() const;

      const FVector2& GetSize() const;

      Settings::EHorizontalAlignment GetHorizontalAlignment() const;

      Settings::EVerticalAlignment GetVerticalAlignment() const;

    protected:
      void Update();
      virtual void _Draw_Impl() = 0;

    private:
      FVector2 CaculatePositionAlignmentOffset(bool p_default = false);
      
      void UpdatePosition();
      void UpdateSize();
      void CopyImGuiPosition();
      void CopyImGuiSize();

    public:
      bool autoSize = true;
    
    protected:
      FVector2 m_defaultPosition;
      FVector2 m_defaultSize;
      Settings::EHorizontalAlignment m_defaultHorizontalAlignment;
      Settings::EVerticalAlignment m_defaultVerticalAlignment;
      
      bool m_ignoreConfigFile;

      FVector2 m_position = {0.0f, 0.0f};
      FVector2 m_size = {0.0f, 0.0f};

      bool m_positionChanged = false;
      bool m_sizeChanged = false;

      Settings::EHorizontalAlignment m_horizontalAlignment = Settings::EHorizontalAlignment::LEFT;
      Settings::EVerticalAlignment m_verticalAlignment = Settings::EVerticalAlignment::TOP;

      bool m_alignmentChanged = false;
      bool m_firstFrame = true;


  };

}
