#include "ConcreteStates.h"
#include "Relay.h"
#include "PowerMonitor.h"

#ifdef INTERLOCK
std::unique_ptr<State> AccessGrantedState::doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser, EspMQTTClient &mqttClient) {
    logger.log("Entered access granted state", DEBUG);
    indicator.setColor(GREEN);
    closeRelay(true);

    auto powerOnAction = []{}; // TODO Log with MQTT
    auto powerOffAction = []{}; // TODO Log with MQTT

    PowerMonitor powerMonitor(logger, powerOnAction, powerOffAction);

    while (!cardReader.cardIsAvailable()) { 
        powerMonitor.loop();
        mqttClient.loop();
    }
    return std::make_unique<IdleState>(IdleState());
}
#endif

#ifdef DOOR
State AccessGrantedState::doAction(Logger &logger, Indicator &indicator, RFIDReader &cardReader, CardAuthouriser &authoriser) {
    indicator.setColor(GREEN);
    closeRelay(true);
    delay(15000);
    return std::make_unique<IdleState>(IdleState());
}
#endif