#pragma once

#include "CColor.h"
#include <stdint.h>
#include "IDisplay.h"

class CFrameBuffer
{
public:
    CFrameBuffer(IDisplay &display, uint8_t brightness);
    ~CFrameBuffer();
    CFrameBuffer(const CFrameBuffer &obj);
    CFrameBuffer &operator=(const CFrameBuffer &obj);

    uint32_t size();
    void fill(CColor color);

    void draw(uint32_t x, uint32_t y, CColor color);
    uint32_t width();
    uint32_t height();
    CColor color_at(uint32_t x, uint32_t y);
    void show();

private:
    CColor color_with_correction(CColor color);
    const uint32_t m_width;
    const uint32_t m_height;
    const uint32_t m_size;
    const uint8_t m_brightness;
    IDisplay &m_display;
    CColor *m_pixels;
};
