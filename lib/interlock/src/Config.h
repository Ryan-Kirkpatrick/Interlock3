#pragma once

#define strconcat(a,b) a b

namespace Config {
    // Wifi
    inline const char* wifiSSID = WIFI_SSID;
    inline const char* wifiPassword = WIFI_PASSWORD;

    // MQTT
    inline const char* deviceName = DEVICE_NAME;
    inline const char* brokerAddress = BROKER_ADDRESS;
    inline const int brokerPort = BROKER_PORT;
    inline const char* mqttPassword = MQTT_PASSWORD;
    inline const char* mqttUsername = MQTT_USERNMAE;
    inline const char* inTopic = strconcat(IN_TOPIC,DEVICE_NAME);
    inline const char* outTopic = strconcat(OUT_TOPIC,DEVICE_NAME);
    inline const char* logTopic = strconcat(LOG_TOPIC,DEVICE_NAME);

    // OTA
    inline const char* otaPassword = OTA_PASSWORD;

    // LED
    inline const int numberOfLEDs = N_LEDS;
    inline const int indicatorLEDPin = 2;

    // RFID
    inline const long skeletonKeyCardNumber = SKELETON_CARD; // This card number will allways grant access
    inline const int rfidIgnoreTime = 5; // In seconds

    // IO
    inline const int relayPin = 0;
}