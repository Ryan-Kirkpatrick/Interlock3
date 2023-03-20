#pragma once

#include <optional>
#include <string>
#include "Types.hpp"
#include "Core.hpp"
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "Cache.hpp"
#include "Logger.hpp"

class IPortalConnection {
    public:
        virtual std::optional<std::string> obtainHashOfAuthedCards(WiFiClient &wifiClient) = 0;
        virtual std::optional<CachedRFIDCards> getAllAuthedCards(WiFiClient &wifiClient) = 0;
        virtual std::optional<bool> checkCardAuth(WiFiClient &wifiClient, RFIDCard card) = 0;
};

class PortalConnection : public IPortalConnection {
    public:
        PortalConnection(Logger &logger);
        std::optional<std::string> obtainHashOfAuthedCards(WiFiClient &wifiClient) override;
        std::optional<CachedRFIDCards> getAllAuthedCards(WiFiClient &wifiClient) override;
        std::optional<bool> checkCardAuth(WiFiClient &wifiClient, RFIDCard card) override;
    protected:
        std::optional<std::string> decodeHashOfAuthedCards(String payload);
        std::optional<CachedRFIDCards> decodeAllAuthedCards(String payload);
        std::optional<bool> decodeCardAuth(String payload);
        std::optional<String> httpGET(WiFiClient &wifiCLient, const char *url);
        Logger &logger;
};