#include "Indicator.h"


void Indicator::setColor(IndicatorColor color) {
    RgbwColor ledColor;
    switch (color) {
        case IndicatorColor::BLUE:
            ledColor = RgbwColor(0, 0, 255, 0);
            break;
        case IndicatorColor::RED:
            ledColor = RgbwColor(255, 0, 0, 0);
            break;
        case IndicatorColor::GREEN:
            ledColor = RgbwColor(0, 255, 0, 0);
            break;
        case IndicatorColor::PURPLE:
            ledColor = RgbwColor(255, 0, 255, 0);
            break;
    }

    for (int i = 0; i < Config::numberOfLEDs; i++) {
        led.SetPixelColor(i, ledColor);
    }
    led.Show();
}

Indicator::Indicator(IndicatorColor startingColor) {
    setColor(startingColor);
}
