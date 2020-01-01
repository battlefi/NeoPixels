#pragma once

#include "CColor.h"
#include <stdint.h>
#include "IDisplay.h"

class CFrameBuffer
{
public:
    CFrameBuffer(IDisplay &display);
    ~CFrameBuffer();
    CFrameBuffer(const CFrameBuffer &obj);
    CFrameBuffer &operator=(const CFrameBuffer &obj);

    uint32_t size();
    void fill(CColor color);
    void fill(uint32_t H, double S, double V);

    void draw(uint32_t x, uint32_t y, CColor color);
    void draw(uint32_t x, uint32_t y, uint32_t H, double S, double V);
    uint32_t width();
    uint32_t height();
    CColor color_at(uint32_t x, uint32_t y);
    void show();

private:
    const uint32_t m_width;
    const uint32_t m_height;
    const uint32_t m_size;
    IDisplay &m_display;
    CColor *m_pixels;
};
