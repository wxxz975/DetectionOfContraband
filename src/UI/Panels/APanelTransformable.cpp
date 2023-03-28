#include "UI/Panels/APanelTransformable.h"
#include <imgui/imgui.h>


DcUI::Panels::APanelTransformable::APanelTransformable(
    FVector2 p_defaultPosition,
    FVector2 p_defaultSize,
    Settings::EHorizontalAlignment p_defaultHorizontalAlignment,
    Settings::EVerticalAlignment p_defaultVerticalAlignment,
    bool p_ignoreConfigFile
    )
    : m_defaultPosition(p_defaultPosition)
    , m_defaultSize(p_defaultSize)
    , m_defaultHorizontalAlignment(p_defaultHorizontalAlignment)
    , m_defaultVerticalAlignment(p_defaultVerticalAlignment)
    , m_ignoreConfigFile(p_ignoreConfigFile)
{
}


void DcUI::Panels::APanelTransformable::SetPosition(const FVector2& p_position)
{
    m_position = p_position;
    m_positionChanged = true;
}

void DcUI::Panels::APanelTransformable::SetSize(const FVector2& p_size)
{
    m_size = p_size;
    m_sizeChanged = true;
}

void DcUI::Panels::APanelTransformable::SetAlignment(Settings::EHorizontalAlignment p_horizontalAlignment, 
    Settings::EVerticalAlignment p_verticalAlignment)
{
    m_horizontalAlignment = p_horizontalAlignment;
    m_verticalAlignment = p_verticalAlignment;
    m_alignmentChanged = true;
}

const Common::Math::FVector2& DcUI::Panels::APanelTransformable::GetPosition() const
{
    return m_position;
}


const Common::Math::FVector2& DcUI::Panels::APanelTransformable::GetSize() const
{
    return m_size;
}


DcUI::Settings::EHorizontalAlignment DcUI::Panels::APanelTransformable::GetHorizontalAlignment() const
{
    return m_horizontalAlignment;
}

DcUI::Settings::EVerticalAlignment DcUI::Panels::APanelTransformable::GetVerticalAlignment() const
{
    return m_verticalAlignment;
}


void DcUI::Panels::APanelTransformable::UpdatePosition()
{
  if(m_defaultPosition[0] != -1.f && m_defaultPosition[1] != -1.f)
  {
    auto temp = CaculatePositionAlignmentOffset(true);
    Common::Math::FVector2 offsettedDefaultPos = 
       { m_defaultPosition[0] + temp[0], m_defaultPosition[1] + temp[1] };
    
    ImGui::SetWindowPos(ImVec2(offsettedDefaultPos[0], offsettedDefaultPos[1]), 
        m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
  }
 
  if(m_positionChanged || m_alignmentChanged)
  {
    Common::Math::FVector2 offset = CaculatePositionAlignmentOffset(false);
    Common::Math::FVector2 offsettedPos = {m_position[0] + offset[0], m_position[1] + offset[1]};
    ImGui::SetWindowPos(ImVec2(offsettedPos[0], offsettedPos[1]), ImGuiCond_Always);
    m_positionChanged = false;
    m_alignmentChanged = false;
  }
}

void DcUI::Panels::APanelTransformable::UpdateSize()
{
  /*if(m_defaultSize[0] != -1.f && m_defaultSize[1] != -1.f)*/
  /*{*/
    /*ImGui::SetWindowSize(ImVec2(m_defaultSize[0], m_defaultSize[1]), */
        /*m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);*/
  /*}*/
 
  if(m_sizeChanged)
  {
    ImGui::SetWindowSize(ImVec2(m_size[0], m_size[1]), ImGuiCond_Always);
    m_sizeChanged = false;
  }
}

void DcUI::Panels::APanelTransformable::CopyImGuiPosition()
{
  ImVec2 pos = ImGui::GetWindowPos();
  m_position = {pos.x, pos.y};
}

void DcUI::Panels::APanelTransformable::CopyImGuiSize()
{
  ImVec2 size = ImGui::GetWindowSize();
  m_size = {size.x, size.y};
}


void DcUI::Panels::APanelTransformable::Update()
{
  if(!m_firstFrame)
  {
    if(!autoSize)
      UpdateSize();

    CopyImGuiSize();

    UpdatePosition();

    CopyImGuiPosition();
  }

  m_firstFrame = false;
}

Common::Math::FVector2 DcUI::Panels::APanelTransformable::CaculatePositionAlignmentOffset(bool p_default)
{
  Common::Math::FVector2 result = {0.f, 0.f};

  switch (p_default ? m_defaultHorizontalAlignment : m_horizontalAlignment)
  {
    case Settings::EHorizontalAlignment::CENTER:
      result[0] -= m_size[0] / 2.f;
      break;
    case Settings::EHorizontalAlignment::RIGHT:
      result[0] -= m_size[0];
      break;
    default:
      break;
  }

  switch (p_default ? m_defaultVerticalAlignment : m_verticalAlignment)
  {
    case Settings::EVerticalAlignment::MIDDLE:
      result[1] -= m_size[1] / 2.f;
      break;
    case Settings::EVerticalAlignment::BOTTOM:
      result[1] -= m_size[1];
      break;
    default:
      break;
  }

  return result;
}

