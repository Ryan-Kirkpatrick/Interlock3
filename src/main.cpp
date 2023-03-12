#include <Arduino.h>

#include "RFIDReader.hpp"
#include "MockSerial.hpp"
#include <string>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>
#include <Indicator.hpp>
#include <ESP8266WebServer.h>

#include <PortalConnection.hpp>
#include <HTTPInterface.hpp>

PortalConnection portal;
HTTPInterface http(portal);
Logger logger;

void setup() {
    Serial.begin(9600);
	while (!Serial) {

	}
    WiFi.begin("", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.println("...");
    }

}

void loop() {
    http.loop();
    delay(100);
}

