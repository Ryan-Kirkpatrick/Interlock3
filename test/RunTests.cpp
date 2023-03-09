#include <gtest/gtest.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

TEST(TEST, Tests_Running) {
	ASSERT_TRUE(true);
}

#define private public
#include "RFIDReader_test.hpp"
#include "InterlockState_test.hpp"

#ifdef ARDUINO
#include <Arduino.h>
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

#else

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
	if (RUN_ALL_TESTS()) {
        // Left intentionally empty, PIO does not require the result and it cannot be cast to void.
    }
	return 0;
}
#endif