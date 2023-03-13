#pragma once

#include <optional>
#include <string>
#include "Types.hpp"
#include "Core.hpp"
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "Cache.hpp"
#include "Logger.hpp"


class PortalConnection {
    public:
        PortalConnection(Logger &logger);
        PortalConnection() = delete;
        virtual std::optional<std::string> obtainHashOfAuthedCards(WiFiClient &wifiClient);    
        virtual std::optional<CachedRFIDCards> getAllAuthedCards(WiFiClient &wifiClient);
        virtual std::optional<bool> checkCardAuth(WiFiClient &wifiClient, RFIDCard card);
    protected:
        static std::optional<std::string> decodeHashOfAuthedCards(String payload);
        static std::optional<CachedRFIDCards> decodeAllAuthedCards(String payload);
        static std::optional<bool> decodeCardAuth(String payload);
        static std::optional<String> httpGET(WiFiClient &wifiCLient, const char *url);
        Logger &logger;
};