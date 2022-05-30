#pragma once

#include <EspMQTTClient.h>
#include "Cache.h"
#include "Logger.h"
#include "Card.h"

class CardAuthouriser {
    private:
        bool awaitingMQTTResponse; // Used to wait for an MQTT response when checking a card.
        EspMQTTClient& client;
        Logger& logger;
        std::string hashOfCards;
        std::vector<Card> cards;
        Cache cache;
        // Decode the cards from the MQTT payload
        void updateAuthourisedCardList(std::string mqttPayload);
        
    public:
        CardAuthouriser(EspMQTTClient& mqttClient,  Logger& logger);
        bool checkCard(Card card);
        // Subscribes to authourisation topic, called when a connection to the MQTT broker is established
        void resubscribe();
};