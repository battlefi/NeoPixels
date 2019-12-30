#pragma once

#include "CNeoPixels.h"
#include "IDisplay.h"

class CNeoMatrix : public CNeoPixels, public IDisplay
{
public:
    CNeoMatrix(rmt_channel_t channel, gpio_num_t gpio, uint32_t width, uint32_t height, EType type);
    void show(CColor *pixels) override;
    uint32_t width() override;
    uint32_t height() override;

private:
    const uint32_t m_width;
    const uint32_t m_height;
};
