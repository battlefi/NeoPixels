#pragma once

#include <stdint.h>

class CColor
{
public:
    CColor(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
    CColor() : r(0), g(0), b(0) {}

    static CColor from_hsv(uint32_t H, double S, double V);

    static CColor red() { return CColor(255, 0, 0); };
    static CColor green() { return CColor(0, 255, 0); };
    static CColor blue() { return CColor(0, 0, 255); };
    static CColor black() { return CColor(0, 0, 0); };
    static CColor yellow() { return CColor(255, 255, 0); };


    uint8_t r;
    uint8_t g;
    uint8_t b;
};
