# NeoPixels Component ESP-IDF
ESP-IDF Component to control NeoPixels RGB Leds

## Usage
Clone repo into the components folder

### CNeoPixel

#### Example with 3 LED's
```
CNeoPixels pixels(RMT_CHANNEL_0, GPIO_NUM_18, 3, CNeoPixels::EType::WS2812B);
matrix.brightness(20);
pixels.draw(0, CColor::red());
pixels.draw(1, CColor::green());
pixels.draw(2, CColor::blue());
pixels.flush();
```

### CNeoMatrix

### Example with 8x8 Matrix
```
CNeoMatrix matrix(RMT_CHANNEL_0, GPIO_NUM_18, 8, 8, CNeoPixels::EType::WS2812B);
matrix.brightness(20);
matrix.draw(0, 0, CColor::red());
matrix.draw(1, 1, CColor::green());
matrix.draw(2, 2, CColor::blue());
matrix.flush();
```


## Tests
- [x] Adafruit 8x8 RGB Martrix WS2812B 
