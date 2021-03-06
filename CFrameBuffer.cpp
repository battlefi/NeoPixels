#include "CFrameBuffer.h"

#include <new>
#include <cstring>
#include <assert.h>

CFrameBuffer::CFrameBuffer(IDisplay &display)
    : m_width(display.width()),
      m_height(display.height()),
      m_size(m_width * m_height),
      m_display(display)
{
    assert(m_size > 0);
    m_pixels = new CColor[m_size]();
}

CFrameBuffer::CFrameBuffer(const CFrameBuffer &obj)
    : m_width(obj.m_width),
      m_height(obj.m_height),
      m_size(obj.m_size),
      m_display(obj.m_display)
{
    m_pixels = new CColor[m_size]();
    assert(m_pixels != nullptr);
    std::memcpy(m_pixels, obj.m_pixels, sizeof(CColor) * m_size);
}

CFrameBuffer &CFrameBuffer::operator=(const CFrameBuffer &obj)
{
    if (this == &obj)
        return *this;
    std::memcpy(m_pixels, obj.m_pixels, sizeof(CColor) * m_size);
    return *this;
}

CFrameBuffer::~CFrameBuffer()
{
    delete[] m_pixels;
}

void CFrameBuffer::show()
{
    m_display.show(m_pixels);
}

void CFrameBuffer::draw(uint32_t x, uint32_t y, CColor color)
{
    uint32_t number = x * m_height + y;
    assert(number < m_size);
    m_pixels[number] = color;
}

void CFrameBuffer::draw(uint32_t x, uint32_t y, uint32_t H, double S, double V)
{
    draw(x, y, CColor::from_hsv(H, S, V));
}

CColor CFrameBuffer::color_at(uint32_t x, uint32_t y)
{
    uint32_t number = x * m_height + y;
    assert(number < m_size);
    return m_pixels[number];
}

void CFrameBuffer::fill(CColor color)
{
    for (uint32_t i = 0; i < m_width; ++i)
    {
        for (uint32_t j = 0; j < m_height; ++j)
            draw(i, j, color);
    }
}

void CFrameBuffer::fill(uint32_t H, double S, double V)
{
    fill(CColor::from_hsv(H, S, V));
}

uint32_t CFrameBuffer::size()
{
    return m_size;
}

uint32_t CFrameBuffer::width()
{
    return m_width;
}

uint32_t CFrameBuffer::height()
{
    return m_height;
}
