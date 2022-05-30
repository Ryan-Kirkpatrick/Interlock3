#include "ConcreteStates.h"
#include "Relay.h"

std::unique_ptr<State> IdleState::doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) {
    indicator.setColor(BLUE);
    logger.log("Entered idle state", DEBUG);
    closeRelay(false);

    // Reset card reader
    delay(250);
    cardReader.flush();

    // Wait for card read and select next state
    while (!cardReader.cardIsAvailable()) {
        yield();
        mqttClient.loop();
    }
    indicator.setColor(PURPLE);
    Card card = cardReader.readCard();
    if (authoriser.checkCard(card)) {
        logger.log(std::string("Access granted to ").append(std::to_string(card)));
        return std::make_unique<AccessGrantedState>(AccessGrantedState());
    }
    logger.log(std::string("Access denied to ").append(std::to_string(card)));
    return std::make_unique<AccessDeniedState>(AccessDeniedState());       
}
