# NeoPixels Component ESP-IDF
ESP-IDF Component to control NeoPixels RGB Leds

## Usage
Clone repo into the components folder

### CNeoPixel

#### Example
```
CNeoPixels pixels(RMT_CHANNEL_0, GPIO_NUM_18, 3, CNeoPixels::EType::WS2812B);
pixels.draw(0, CColor::red());
pixels.draw(1, CColor::green());
pixels.draw(2, CColor::blue());
pixels.flush();
```

## Tests
- [x] Adafruit 8x8 RGB Martrix WS2812B 
