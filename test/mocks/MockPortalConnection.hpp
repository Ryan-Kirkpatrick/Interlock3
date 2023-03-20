#pragma once

#include "PortalConnection.hpp"

class MockPortalConnection : IPortalConnection {
    public:
        /**
         * @brief Set if we can connect to the portal or not.
         * 
         */
        bool connectionIsWorking;

        /**
         * @brief When true 
         * 
         */
        bool authorized;

        MockPortalConnection(bool connectionIsWorking, bool authorized) : 
            connectionIsWorking{connectionIsWorking},
            authorized{authorized}
            {}

        std::optional<std::string> obtainHashOfAuthedCards(WiFiClient &wifiClient) override {
            if (!connectionIsWorking) {
                return {};
            }
        }

        std::optional<CachedRFIDCards> getAllAuthedCards(WiFiClient &wifiClient) override {
            if (!connectionIsWorking) {
                return {};
            }
        }

        std::optional<bool> checkCardAuth(WiFiClient &wifiClient, RFIDCard card) override {
            if (!connectionIsWorking) {
                return {};
            }
        }

}

// TODO