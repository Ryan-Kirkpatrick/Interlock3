#pragma once

#include <ESP8266WebServer.h>

#include "Core.hpp"
#include "InterlockState.hpp"
#include "PortalConnection.hpp"


class HTTPInterface {
    public:
        HTTPInterface(PortalConnection &portal);

        /**
         * @brief Must be called frequently to handle HTTP. 
         * Will yield a state if ti has been requested
         * 
         * @return std::optional<std::unique_ptr<AbstractState>> The next state to enter, if any. 
         */
        std::optional<std::unique_ptr<AbstractState>> loop();

    private:
        // HTTP handlers
        void httpRoot(); // Action to take when visiting http://device.local/
        void httpReboot(); // Action to take when visiting http://device.local/reboot
        void httpBump(); // Action to take when visiting http://device.local/bump
        void httpActivate(); // Action to take when visiting http://device.local/activate
        void httpLogs(); // Action to take when visiting http://device.local/logs or http://device.local/log
        void httpRedirectToRoot(); // Redirect to http://device.local/ 

        // Internal state
        ESP8266WebServer httpServer;
        std::optional<std::unique_ptr<AbstractState>> nextState;
        PortalConnection &portal;
};