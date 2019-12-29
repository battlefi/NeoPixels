#include "CNeoPixels.h"

#include <new>
#include <cstring>

CNeoPixels::CNeoPixels(rmt_channel_t channel, gpio_num_t gpio, uint32_t size, EType type)
    : m_channel(channel),
      m_gpio(gpio),
      m_size(size),
      m_type(type),
      m_brightness(100)
{
    assert(size > 0);

    if (type == EType::WS2812B)
    {
        m_logic_zero.level0 = 1;
        m_logic_zero.duration0 = 32;
        m_logic_zero.level1 = 0;
        m_logic_zero.duration1 = 68;

        m_logic_one.level0 = 1;
        m_logic_one.duration0 = 64;
        m_logic_one.level1 = 0;
        m_logic_one.duration1 = 36;
    }

    m_items = new rmt_item32_t[m_size * m_bits_per_pixel]();
    m_pixels = new CColor[m_size]();

    rmt_config_t rmt_tx;
    std::memset(&rmt_tx, 0, sizeof(rmt_config_t));
    rmt_tx.channel = m_channel;
    rmt_tx.gpio_num = m_gpio;
    rmt_tx.mem_block_num = 1;
    rmt_tx.clk_div = 1;
    rmt_tx.tx_config.idle_output_en = 1;
    rmt_config(&rmt_tx);
    rmt_driver_install(rmt_tx.channel, 0, 0);
}

CNeoPixels::~CNeoPixels()
{
    rmt_driver_uninstall(m_channel);
    delete[] m_items;
    delete[] m_pixels;
}

CColor CNeoPixels::color_with_correction(CColor color)
{
    return CColor(color.r * m_brightness / 100, color.g * m_brightness / 100, color.b * m_brightness / 100);
}

void CNeoPixels::draw(uint32_t number, CColor color)
{
    assert(number < m_size);
    m_pixels[number] = color_with_correction(color);
}

void CNeoPixels::draw(uint32_t number, uint8_t r, uint8_t g, uint8_t b)
{
    draw(number, CColor(r, g, b));
}

void CNeoPixels::fill(CColor color)
{
    for(uint32_t i = 0; i < m_size; ++i)
    {
        draw(i, color);
    }
}

void CNeoPixels::fill(uint8_t r, uint8_t g, uint8_t b)
{
    fill(CColor(r, g, b));
}

CColor *CNeoPixels::pixels()
{
    return m_pixels;
}

uint32_t CNeoPixels::size()
{
    return m_size;
}

void CNeoPixels::brightness(uint8_t max_brightness_percent)
{
    m_brightness = max_brightness_percent;
    // TODO: apply correction to current pixels
}

void CNeoPixels::flush()
{
    unsigned int itemCnt = 0;

    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_bits_per_pixel; j++)
        {
            if (j < 8)
            {
                if (m_pixels[i].g & (1 << (7 - j)))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }

            else if (j < 16)
            {
                if (m_pixels[i].r & (1 << (7 - (j % 8))))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }
            else
            {
                if (m_pixels[i].b & (1 << (7 - (j % 8))))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }
        }
    rmt_write_items(m_channel, m_items, m_size * m_bits_per_pixel, false);
}
