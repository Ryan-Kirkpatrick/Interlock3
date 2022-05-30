#pragma once

#include "State.h"

class IdleState : public State {
    public:
        std::unique_ptr<State> doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser,EspMQTTClient &mqttClient) override;
};

class AccessGrantedState : public State {
    private:
        void (*powerOffAction)(void);
        void (*powerOnAction)(void);
    public:
        std::unique_ptr<State> doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) override;
};

class AccessDeniedState : public State {
    public:
        std::unique_ptr<State> doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) override;
};
