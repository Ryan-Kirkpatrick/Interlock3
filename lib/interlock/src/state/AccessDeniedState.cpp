#include "ConcreteStates.h"

std::unique_ptr<State> AccessDeniedState::doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) {
    indicator.setColor(RED);
    logger.log("Entered access denied state", DEBUG);
    delay(3000);
    return std::make_unique<IdleState>(IdleState());
}