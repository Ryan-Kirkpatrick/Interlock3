#include <Arduino.h>
#include <gtest/gtest.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>
#include "Core.hpp"

#define private public
#include "RFIDReader_test.hpp"
#include "InterlockState_test.hpp"
#include "Cache_test.hpp"

void setup() {
	Serial.begin(9600);
	::testing::InitGoogleTest();
}

void loop() {
	if (RUN_ALL_TESTS()) {
        // Left intentionally empty, PIO does not require the result and it cannot be cast to void.
    }
	delay(1000);
}