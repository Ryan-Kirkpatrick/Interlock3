#include <Arduino.h>

#include "RFIDReader.hpp"
#include "MockSerial.hpp"
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {
    Serial.begin(9600);
	while (!Serial) {

	}

    WiFi.begin("hi", "bob");

}

void loop() {
    delay(1000);
    Serial.println("Starting.");
    MockSerial serial;
    uint8_t bytes[] = {0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x38, 0xfb, 0x3};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    Serial.println(card.has_value());
}

