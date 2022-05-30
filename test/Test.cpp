#include <unity.h>
#include <Arduino.h>
#include <EspMQTTClient.h>

#include "Config.h"
#include "CardAuthoriser.h"
#include "Logger.h"

EspMQTTClient mqttClient (
        Config::wifiSSID,
        Config::wifiPassword,
        Config::brokerAddress,
        Config::mqttUsername,
        Config::mqttPassword,
        Config::deviceName,
        Config::brokerPort
);
Logger logger(mqttClient);
CardAuthouriser auth(mqttClient, logger);

void onConnectionEstablished() {
    auth.resubscribe();
}

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


/**
 * Tests the MQTT card authouriser while the MQTT system is working normally.
 */
void testMQTTNormal() {
    TEST_ASSERT_TRUE(auth.checkCard(1143751));
}


void setup() {
    Serial.begin(9600);
    UNITY_BEGIN();
    while (!mqttClient.isConnected()) {
        delay(500);
        mqttClient.loop();
        Serial.println("Waiting for connection...");
    }
    RUN_TEST(testMQTTNormal);
    UNITY_END();
}

void loop() {
    mqttClient.loop();
}
