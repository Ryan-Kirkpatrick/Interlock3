#pragma once

#include <NeoPixelBus.h>
#include "Core.hpp"

typedef RgbwColor IndicatorColorRGBW;
namespace IndicatorColors {
    const IndicatorColorRGBW RED = IndicatorColorRGBW(255, 0, 0, 0);
    const IndicatorColorRGBW GREEN = IndicatorColorRGBW(0, 255, 0, 0);
    const IndicatorColorRGBW BLUE = IndicatorColorRGBW(0, 0, 0, 255);
    const IndicatorColorRGBW WHITE = IndicatorColorRGBW(255, 255, 255, 255);
    const IndicatorColorRGBW PURPLE = IndicatorColorRGBW(255, 0, 255, 0);
    const IndicatorColorRGBW YELLOW = IndicatorColorRGBW(255, 255, 0, 0);
}

class Indicator {
    public:
        Indicator(IndicatorColorRGBW startingColor);
        
        /**
         * @brief Changes the color of the indicator.
         * 
         * @param color The color to set the indicator to.
         */
        void update(IndicatorColorRGBW color);
    private:
        IndicatorColorRGBW _currentColor;
        #ifdef ARDUINO
        #ifdef GRBW
        NeoPixelBus<NeoGrbwFeature, NeoEsp8266BitBang800KbpsMethod> led = NeoPixelBus<NeoGrbwFeature, NeoEsp8266BitBang800KbpsMethod>(Core::NUMBER_OF_INDICATOR_LEDS, Core::INDICATOR_LED_PIN);
        #endif
        #ifdef RGBW
        NeoPixelBus<NeoRgbwFeature, NeoEsp8266BitBang800KbpsMethod> led = NeoPixelBus<NeoRgbwFeature, NeoEsp8266BitBang800KbpsMethod>(Core::NUMBER_OF_INDICATOR_LEDS, Core::INDICATOR_LED_PIN);
        #endif
        #endif
};