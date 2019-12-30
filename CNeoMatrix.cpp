#include "CNeoMatrix.h"

CNeoMatrix::CNeoMatrix(rmt_channel_t channel, gpio_num_t gpio, uint32_t width, uint32_t height, EType type)
    : CNeoPixels(channel, gpio, width * height, type),
      m_width(width),
      m_height(height)
{
}
void CNeoMatrix::show(CColor *pixels)
{
    CNeoPixels::show(pixels);
}

uint32_t CNeoMatrix::width()
{
    return m_width;
}

uint32_t CNeoMatrix::height()
{
    return m_height;
}
