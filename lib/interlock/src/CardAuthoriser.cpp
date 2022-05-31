#include "CardAuthoriser.h"
#include "Config.h"
#include <sstream>

CardAuthouriser::CardAuthouriser(EspMQTTClient& mqttClient, Logger& logger) : client{mqttClient}, logger{logger}, cache{Cache(logger)} {
    cache.read(cards);
}

/**
 * The first line of the message will always be a hash. The following lines will be card numbers. Ex
 * 793561292546532022
 * 489586
 * 984856
 * 094859
 */
void CardAuthouriser::updateAuthourisedCardList(std::string msg) {
    logger.log("Recevied card list", DEBUG);
    bool cardsNeedUpdating = false;
    auto ss = std::istringstream(msg);
    for(std::string line; std::getline(ss ,line, '\n'); ) {;
        if (cardsNeedUpdating) {
            cards.push_back(std::stol(line.c_str(), nullptr));
        } else {
            // The hash of the cards is the same. No need to decode them again.
            if (line == hashOfCards) {
                break;
            }
            // The hash is differnt. Decode the cards and cache them.
            cards.clear();
            hashOfCards = line;
            cardsNeedUpdating = true;
        }
    }

    if (cardsNeedUpdating) {
        cache.replace(cards);
    }

    awaitingMQTTResponse = false;
}

void CardAuthouriser::resubscribe() {
    client.subscribe(Config::inTopic, [this](const String& msg) {
        this->updateAuthourisedCardList(msg.c_str());
    });
}

bool CardAuthouriser::checkCard(Card card) {
    logger.log(("Checking card " + String(card)).c_str());
    // Publish the card number and wait for the MQTT response with a timout
    client.loop();
    logger.log(std::to_string(client.isConnected()), DEBUG);
    if (client.isConnected()) {
        awaitingMQTTResponse = true;
        client.publish(Config::outTopic, std::to_string(card).c_str());
        auto currentTime = millis();
        while (awaitingMQTTResponse && (millis() - currentTime) < 4000) {
            client.loop();
        }
        if (awaitingMQTTResponse) {
            logger.log("The MQTT response timed out. Checking cache.");
        }
        awaitingMQTTResponse = false;
    }

    // Check if the card is authourised
    for (Card currentCard : cards) {
        if (card == currentCard) {
            return true;
        }
    }
    return false;
}
