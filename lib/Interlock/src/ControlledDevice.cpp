#include "ControlledDevice.hpp"
#include <Arduino.h>

ControlledDevice::ControlledDevice(uint8_t gpioPin, bool relayNormallyClosed) :
gpioPin{gpioPin},
relayNormallyClosed{relayNormallyClosed} {
    pinMode(gpioPin, OUTPUT);
    turnOff();
}

void ControlledDevice::turnOn() {
    if (relayNormallyClosed) {
        digitalWrite(gpioPin, LOW);
    } else {
        digitalWrite(gpioPin, HIGH);
    }
}

void ControlledDevice::turnOff() {
    if (relayNormallyClosed) {
        digitalWrite(gpioPin, HIGH);
    } else {
        digitalWrite(gpioPin, LOW);
    }
}
