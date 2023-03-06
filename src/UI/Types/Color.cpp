#include "UI/Types/Color.h"

const DcUI::Types::Color DcUI::Types::Color::Red = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Green = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Blue = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::While = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Black = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Grey = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Yellow = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Cyan = {1.f, 0.f, 0.f};
const DcUI::Types::Color DcUI::Types::Color::Magenta = {1.f, 0.f, 0.f};


DcUI::Types::Color::Color(float p_r, float p_g, float p_b, float p_a)
  :r(p_r), g(p_g), b(p_b), a(p_a)
{
}

bool DcUI::Types::Color::operator==(const Color& p_other)
{
  return r == p_other.r && g == p_other.g && b == p_other.b && a == p_other.a;  
}

bool DcUI::Types::Color::operator!=(const Color& p_other)
{
  return !operator==(p_other);
}

