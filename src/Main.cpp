#include <Arduino.h>
#include <EspMQTTClient.h>
#include <Scheduler.h>
#include <ESP8266WiFi.h>

#include "Config.h"
#include "CardAuthoriser.h"
#include "Logger.h"
#include "Indicator.h"
#include "RFIDReader.h"
#include "state/State.h"
#include "state/StateMachine.h"
#include "state/ConcreteStates.h"

// MQTT, Wifi, and OTA setup
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
CardAuthouriser authouriser(mqttClient, logger);
Indicator indicator(PURPLE);
RFIDReader cardReader(logger);
StateMachine stateMachine(std::make_unique<IdleState>(IdleState()), logger, indicator, cardReader, authouriser, mqttClient);

void setup() {
    Serial.begin(9600);
    mqttClient.enableOTA(Config::otaPassword, 8266);
    mqttClient.setKeepAlive(60);
    mqttClient.setMqttReconnectionAttemptDelay(1); // TODO Remove this line or set a reasonable delay
    mqttClient.loop();
    while (!Serial) { delay(100); }
}

void loop() {
    mqttClient.loop();
    stateMachine.run();
}

// This function has to be implemented, it's a requirement of the EspMQTTClient library.
void onConnectionEstablished() {
    logger.log("MQTT connection established");
    Serial.println(WiFi.localIP());
    authouriser.resubscribe();
}