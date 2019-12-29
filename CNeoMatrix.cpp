#include "CNeoMatrix.h"

CNeoMatrix::CNeoMatrix(rmt_channel_t channel, gpio_num_t gpio, uint32_t rows, uint32_t columns, EType type)
    : CNeoPixels(channel, gpio, rows * columns, type),
      m_rows(rows),
      m_columns(columns)
{
}

void CNeoMatrix::draw(uint32_t row, uint32_t column, CColor color)
{
    uint32_t number = row * m_columns + column;
    CNeoPixels::draw(number, color);
}

void CNeoMatrix::draw(uint32_t row, uint32_t column, uint8_t r, uint8_t g, uint8_t b)
{
    draw(row, column, CColor(r, g, b));
}
