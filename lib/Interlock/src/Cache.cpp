#include "Cache.hpp"

#include <LittleFS.h>
#include <stdlib.h>

const char* Cache::CACHE_FILE_NAME = "cache.txt";

Cache::Cache(Logger &logger) : logger{logger} {}

bool Cache::checkCard(const RFIDCard card) {
    // Load cache, if required
    if (!cacheInMemory) {
        if (!deserializeCache()) {
            return false; // Could not retrieve cache.
        }
    }

    // Check cache
    for (uint16_t i = 0; i < cachedCards.numberOfCards; i++) {
        if (cachedCards.cards[i] == card) {
            return true;
        }
    }
    return false;
}

bool Cache::update(const CachedRFIDCards &newCache) {
    // Obtain the current hash value, or fail
    if (!cacheInMemory) {
        if (!deserializeCache()) {
            return false; // Could not retrieve cache.
        }
    }
    if (!serializeCache(newCache)) {
        return false; // Fail if cache could not be written.
    }

    // Update cache in memory
    cachedCards.hashOfCards = newCache.hashOfCards;
    cachedCards.numberOfCards = newCache.numberOfCards;
    (void) std::memcpy(cachedCards.cards, newCache.cards, Core::CACHE_SIZE * sizeof(RFIDCard));
    
    return true;
}

std::optional<std::string> Cache::getHash() {
    if ((cacheInMemory) && (cachedCards.hashOfCards != "")) {
        return cachedCards.hashOfCards;
    }
    return {};
}

// Format: (items separated by '\n')
// 498594-38548-458948-3983   <-- hash
// 878943                     <-- cards
// 384833
// 848754
// \03                        <-- ETX byte with \n
// 

bool Cache::serializeCache(const CachedRFIDCards &newCache) {
    // Open file for writing
    if (!LittleFS.begin()) {
        return false;
    }
    File cacheFile = LittleFS.open(CACHE_FILE_NAME, "w");
    if (!cacheFile) {
        return false;
    }

    // Write
    // Hash
    cacheFile.print((newCache.hashOfCards + "\n").c_str());
    // Cards
    for (uint16_t i = 0; i < newCache.numberOfCards; i++) {
        cacheFile.print((std::to_string(newCache.cards[i]) + "\n").c_str());
    }
    // ETX
    cacheFile.print("\03\n");

    // Clean up
    cacheFile.close();

    return true;
}

bool Cache::deserializeCache() {
    if (!LittleFS.begin()) {
        return false;
    }
    
    // Check if file exists
    if (!LittleFS.exists(CACHE_FILE_NAME)) {
        cacheInMemory = true;
        return true;
    }
    
    // Open file for reading
    File cacheFile = LittleFS.open(CACHE_FILE_NAME, "r");
    if (!cacheFile) {
        return false;
    }

    // Read
    cachedCards.hashOfCards = cacheFile.readStringUntil('\n').c_str();
    std::string buffer = cacheFile.readStringUntil('\n').c_str();
    uint16_t cardCount = 0;
    while ((buffer != "\03") && (cardCount < Core::CACHE_SIZE)) {
        cachedCards.cards[cardCount] = strtoul(buffer.c_str(), nullptr, 10);
        cardCount++;
    }
    cachedCards.numberOfCards = cardCount;

    // Clean up
    cacheFile.close();

    // Update state
    cacheInMemory = true;

    return true;
}
