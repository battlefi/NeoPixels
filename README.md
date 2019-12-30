# NeoPixels Component ESP-IDF
ESP-IDF Component to control NeoPixels RGB Leds

## Usage
Clone repo into the components folder

### CNeoPixel

#### Example with 3 LED's
```cpp
CNeoPixels stripe(RMT_CHANNEL_0, GPIO_NUM_18, 3, CNeoPixels::EType::WS2812B);
CColor pixels[3];
pixels[0] = CColor::red();
pixels[1] = CColor::green();
pixels[2] = CColor::blue();
stripe.show(pixels);
```

### CNeoMatrix

#### Example with 8x8 Matrix
```cpp
CNeoMatrix display(RMT_CHANNEL_0, GPIO_NUM_18, 8, 8, CNeoPixels::EType::WS2812B);
CFrameBuffer fb(display, 20);
fb.draw(0, 0, CColor::red());
fb.draw(1, 1, CColor::green());
fb.draw(2, 2, CColor::blue());
fb.show();
```


## Tests
- [x] Adafruit 8x8 RGB Martrix WS2812B 
