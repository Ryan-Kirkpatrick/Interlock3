#define INTERLOCK_UNIT_TEST

#include <Arduino.h>
#include <gtest/gtest.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#include "Core.hpp"

#define private public
#define protected public
#include "RFIDReader_test.hpp"
#include "InterlockState_test.hpp"
#include "Cache_test.hpp"
#include "Logger_test.hpp"

void setup() {
	Serial.begin(9600);
	::testing::InitGoogleTest();
}

void loop() {
	if (RUN_ALL_TESTS()) {
        // Left intentionally empty, PIO does not require the result and it cannot be cast to void.
    }
	Serial.println("All tests complete");
	delay(1000);
}