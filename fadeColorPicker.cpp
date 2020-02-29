#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    double distSq = sqrt(pow(p.x - p.c.x, 2) + pow(p.y - p.c.y, 2));
    double newL = p.c.color.l * pow(fadeFactor, distSq);
    HSLAPixel newColor = HSLAPixel(p.c.color.h, p.c.color.s, newL);
    return newColor;
}
