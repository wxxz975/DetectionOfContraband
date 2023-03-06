
#include "UI/Internal/Converter.h"




DcUI::Types::Color DcUI::Internal::Converter::ToColor(const ImVec4& p_value)
{
  return Types::Color(p_value.x, p_value.y, p_value.z, p_value.w);
}


ImVec4 DcUI::Internal::Converter::ToImVec4(const Types::Color& p_value)
{
  return ImVec4(p_value.r, p_value.g, p_value.b, p_value.a);
}
