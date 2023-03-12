#pragma once

#include <stdint.h>
#include <cstddef>

namespace Core {
    // Pin config
    inline const uint8_t INDICATOR_LED_PIN = 14;

    // LED
    inline const uint8_t NUMBER_OF_INDICATOR_LEDS = N_LEDS;

    // Cache
    inline const uint16_t CACHE_SIZE = 100;

    // Device
    #define DEVICE_NAME "TEST"

    // Logging
    inline const size_t LOG_SIZE = 512; // Size of the log buffer in bytes

}