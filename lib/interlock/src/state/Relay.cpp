#include "Relay.h"

void closeRelay(bool relayState) {
    if (relayState) {
        digitalWrite(Config::relayPin, HIGH);
    } else {
        digitalWrite(Config::relayPin, LOW);
    }
}