#include "customColorPicker.h"

customColorPicker::customColorPicker()
{

}

HSLAPixel customColorPicker::operator()(point p)
{
  HSLAPixel newColor = HSLAPixel(360 - p.c.color.h, p.c.color.s, p.c.color.l);
  return newColor;
}
