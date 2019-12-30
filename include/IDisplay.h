#pragma once

#include "CColor.h"

class IDisplay
{
public:
    virtual ~IDisplay() {}
    virtual void show(CColor *pixels) = 0;
    virtual uint32_t width() = 0;
    virtual uint32_t height() = 0;
};
