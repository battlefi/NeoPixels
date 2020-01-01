#include "CNeoPixels.h"

#include <new>
#include <cstring>

CNeoPixels::CNeoPixels(rmt_channel_t channel, gpio_num_t gpio, uint32_t size, EType type)
    : m_channel(channel),
      m_gpio(gpio),
      m_size(size),
      m_type(type)
{
    assert(m_size > 0);

    intensity(1);

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
}

uint32_t CNeoPixels::size()
{
    return m_size;
}

void CNeoPixels::intensity(double intensity)
{
    assert(intensity >= 0);
    assert(intensity <= 1);
    m_intensity = intensity;

    // range of m_scale 0 - 256,  -> 256 == 100%
    m_scale = static_cast<uint16_t>(256.0 * intensity);
}

void CNeoPixels::show(CColor *pixels)
{
    unsigned int itemCnt = 0;

    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_bits_per_pixel; j++)
        {
            if (j < 8)
            {
                if (((pixels[i].g * m_scale) >> 8) & (1 << (7 - j)))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }

            else if (j < 16)
            {
                if (((pixels[i].r * m_scale) >> 8) & (1 << (7 - (j % 8))))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }
            else
            {
                if (((pixels[i].b * m_scale) >> 8) & (1 << (7 - (j % 8))))
                    m_items[itemCnt++] = m_logic_one;
                else
                    m_items[itemCnt++] = m_logic_zero;
            }
        }
    rmt_write_items(m_channel, m_items, m_size * m_bits_per_pixel, false);
}
