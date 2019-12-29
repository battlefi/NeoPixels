#pragma once

#include "CNeoPixels.h"

class CNeoMatrix : public CNeoPixels
{
    public:
    CNeoMatrix(rmt_channel_t channel, gpio_num_t gpio, uint32_t rows, uint32_t columns, EType type);
    void draw(uint32_t row, uint32_t column, CColor color);
    void draw(uint32_t row, uint32_t column, uint8_t r, uint8_t g, uint8_t b);

    private:
    const uint32_t m_rows;
    const uint32_t m_columns;

};
