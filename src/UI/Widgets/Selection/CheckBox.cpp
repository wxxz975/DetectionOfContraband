#include "UI/Widgets/Selection/CheckBox.h"
#include "UI/Widgets/DataWidget.h"
#include <imgui/imgui.h>

DcUI::Widgets::Selection::CheckBox::CheckBox(bool p_value, const std::string& p_label): 
  DataWidget<bool>(value), value(p_value), label(p_label)
{

}

void DcUI::Widgets::Selection::CheckBox::_Draw_Impl()
{
  bool previousValue = value;

  
  ImGui::Checkbox((label + this->m_widgetID).c_str(), &value);

  if(value != previousValue)
  {
    ValueChangedEvent.Invoke(value);
    this->NotifyChange();
  }
}
