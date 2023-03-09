#pragma once

#include "Types.hpp"
#include  "Core.hpp"
#include <string>
#include <optional>

struct CachedRFIDCards {
    std::string hashOfCards;
    RFIDCard cards[Core::CACHE_SIZE] = {0};
    uint16_t numberOfCards = 0;
};

class Cache {
    public:
        /**
         * @brief Checks the cache for and RFID card
         * 
         * @param card The card to check for
         * @return True if the card was found. False if not found or on error.
         */
        bool checkCache(RFIDCard card);

        /**
         * @brief Updates the cache.
         * Will take no action if the hash in `authedCards` matches `getCacheHash()` (will still return true)
         * 
         * @param authedCards 
         * @return True for success, false for failure.
         */
        bool updateCache(CachedRFIDCards authedCards);

        /**
         * @brief Gets the hash of the cached cards, used to check if the cache should be updated.
         * 
         * @return The hash of authorised cards in the cache. Will have no value if there was an error with the cache.
         */
        std::optional<std::string> getCacheHash() {

        }

    private:
        bool cacheInMemory = false; // If the cache has been loaded into memory yet.
        CachedRFIDCards cache;
        const char* CACHE_FILE_NAME = "cache.txt";       
};