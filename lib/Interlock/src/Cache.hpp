#pragma once

#include "Types.hpp"
#include "Core.hpp"
#include "Logger.hpp"
#include <string>
#include <optional>

struct CachedRFIDCards {
    std::string hashOfCards;
    RFIDCard cards[Core::CACHE_SIZE];
    uint16_t numberOfCards;
};

class Cache {
    public:

        Cache(Logger &logger);
        Cache() = delete;

        /**
         * @brief Checks the cache for and RFID card
         * 
         * @param card The card to check for
         * @return True if the card was found. False if not found or on error.
         */
        bool checkCard(const RFIDCard card);

        /**
         * @brief Updates the cache.
         * Will take no action if the hash in `newCache` matches `getCacheHash()` (will still return true)
         * 
         * @param newCache 
         * @return True for success, false for failure.
         */
        bool update(const CachedRFIDCards &newCache);

        /**
         * @brief Gets the hash of the cached cards, used to check if the cache should be updated.
         * 
         * @return The hash of authorized cards in the cache. Will have no value if there was an error with the cache.
         */
        std::optional<std::string> getHash();

    private:
        CachedRFIDCards cachedCards = {
            .hashOfCards = "",
            .cards = {},
            .numberOfCards = 0
        };
        static const char* CACHE_FILE_NAME;
        
        bool serializeCache(const CachedRFIDCards &newCache);
        bool deserializeCache();       
        bool cacheInMemory = false; // If the cache has been loaded into memory yet. Only to be altered by deserializeCache()

        Logger &logger;

};