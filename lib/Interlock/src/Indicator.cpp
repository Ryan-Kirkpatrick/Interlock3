#include "Indicator.hpp"


void Indicator::update(IndicatorColorRGBW color) {
    if (color == _currentColor) {
        return;
    }
    for (uint8_t i = 0; i < Core::NUMBER_OF_INDICATOR_LEDS; i++) {
        this->led.SetPixelColor(i, color);
    }
    this->led.Show();
    this->_currentColor = color;
}

Indicator::Indicator(IndicatorColorRGBW startingColor) {
    this->led.Begin();
    update(startingColor);
}