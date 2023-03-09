#pragma once

#include <optional>
#include <string>
#include "Types.hpp"
#include "Core.hpp"
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "Cache.hpp"


class PortalConnection {
    public:
        static std::optional<std::string> obtainHashOfAuthedCards(WiFiClient &wifiClient);    
        static std::optional<CachedRFIDCards> getAllAuthedCards(WiFiClient &wifiClient);
        static std::optional<bool> checkCardAuth(WiFiClient &wifiClient, RFIDCard card);
    private:
        static std::optional<std::string> decodeHashOfAuthedCards(String payload);
        static std::optional<CachedRFIDCards> decodeAllAuthedCards(String payload);
        static std::optional<bool> decodeCardAuth(String payload);
        static std::optional<String> httpGET(WiFiClient &wifiCLient, const char *url);
};