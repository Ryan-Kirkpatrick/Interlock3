#include "StateMachine.h"

StateMachine::StateMachine(std::unique_ptr<State> startingState, Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) : 
    currentState{std::move(startingState)}, 
    logger{logger}, 
    indicator{indicator}, 
    cardReader{cardReader},
    authouriser{authoriser},
    mqttClient{mqttClient}
    {}

void StateMachine::run() {
    currentState = currentState->doAction(logger, indicator, cardReader, authouriser, mqttClient);
}