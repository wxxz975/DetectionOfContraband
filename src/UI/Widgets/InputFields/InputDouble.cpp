#include "UI/Widgets/InputFields/InputDouble.h"


DcUI::Widgets::InputFields::InputDouble::InputDouble(double p_defaultValue, 
    double p_step, double p_fastStep, 
    const std::string& p_label, const std::string& p_format, bool p_selctAllOnClick) : 
  InputSingleScalar<double>(ImGuiDataType_Double, p_defaultValue, p_step, p_fastStep, p_label, p_format, p_selctAllOnClick) {}
