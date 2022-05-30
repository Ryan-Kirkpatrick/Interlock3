#pragma once

#include "Logger.h"
#include "Indicator.h"
#include "RFIDReader.h"
#include "CardAuthoriser.h"
#include <EspMQTTClient.h>
#include <memory>

class State {
    public:
        virtual std::unique_ptr<State> doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) = 0;
};