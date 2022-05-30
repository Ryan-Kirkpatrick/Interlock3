#pragma once

#include <NeoPixelBus.h>
#include "Config.h"

typedef enum {
    RED,
    PURPLE,
    BLUE,
    GREEN
} IndicatorColor;

class Indicator {
    private:
        IndicatorColor color;
        #ifdef GRBW
        NeoPixelBus<NeoGrbwFeature, NeoEsp8266BitBang800KbpsMethod> led = NeoPixelBus<NeoGrbwFeature, NeoEsp8266BitBang800KbpsMethod>(Config::numberOfLEDs, Config::indicatorLEDPin);
        #endif
        #ifdef RGBW
        NeoPixelBus<NeoRgbwFeature, NeoEsp8266BitBang800KbpsMethod> led = NeoPixelBus<NeoRgbwFeature, NeoEsp8266BitBang800KbpsMethod>(Config::numberOfLEDs, Config::indicatorLEDPin);
        #endif
    public:
        void setColor(IndicatorColor color);
        Indicator(IndicatorColor startingColor);

};