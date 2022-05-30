#pragma once

#include "State.h"
#include "Logger.h"
#include "Indicator.h"
#include <memory>
#include <EspMQTTClient.h>

class StateMachine {
    private:
        std::unique_ptr<State> currentState;
        Logger &logger;
        Indicator &indicator;
        RFIDReader &cardReader;
        CardAuthouriser &authouriser;
        EspMQTTClient &mqttClient;

    public:
        StateMachine(std::unique_ptr<State> startingState, Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authorise, EspMQTTClient &mqttClient);
        void run();
};