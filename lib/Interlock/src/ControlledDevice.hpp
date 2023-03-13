#pragma once

#include "Core.hpp"

class ControlledDevice {
    public:
        
        /**
         * @brief Represents the device being controlled using the relay.
         * The device will be off upon creation
         * 
         * @param gpioPin The pin used to turn the relay on/off
         * @param relayNormallyClosed If the relay should be open or closed when the device is off.
         * Set to true if the device should HAVE power when access is denied.
         * Set to false if the device should NOT HAVE power when access is denied 
         */
        ControlledDevice(uint8_t gpioPin, bool relayNormallyClosed);
        
        /**
         * @brief Turn the device on by toggling the relay (access granted)
         */
        void turnOn();

        /**
         * @brief Turn the device off by toggling the relay (access denied)
         */
        void turnOff();

    private:
        const uint8_t gpioPin;
        const bool relayNormallyClosed;
    
};