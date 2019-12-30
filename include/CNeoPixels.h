#pragma once

#include "CColor.h"
#include "driver/rmt.h"

#include <stdint.h>

class CNeoPixels
{
public:
    enum class EType
    {
        WS2812B
    };

    CNeoPixels(rmt_channel_t channel, gpio_num_t gpio, uint32_t size, EType type);
    ~CNeoPixels();
    uint32_t size();
    void show(CColor *pixels);

private:
    const rmt_channel_t m_channel;
    const gpio_num_t m_gpio;
    const uint32_t m_size;
    const EType m_type;
    const uint32_t m_bits_per_pixel = 24;
    rmt_item32_t m_logic_zero;
    rmt_item32_t m_logic_one;
    rmt_item32_t *m_items;
};
