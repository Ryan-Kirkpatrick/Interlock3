#include "Cache.h"
#include <LittleFS.h>
#include <unordered_map>

/**
 * The cahce file consists of the base 10 string representation of a card number, each seperated by a newline (\n). E.g.
 * 211567
 * 345678
 * 287384
 * 958095
 */

Cache::Cache(Logger& logger) : logger{logger} {
    // Mount file system
    if (!LittleFS.begin()) {
        logger.log("Failed to mount filesytem", ERROR);
    } else {
        logger.log("Mounted filestem", DEBUG);
    }
}

void Cache::read(std::vector<Card>& cards) {
    File cacheFile = LittleFS.open("cache.txt", "r");
    if (!cacheFile) {
        logger.log("Failed to open cache file. The cache cannot be read.", ERROR);
        cacheFile.close();
        return;
    }

    while (cacheFile.available()) {
        cards.push_back(std::stol(cacheFile.readStringUntil('\n').c_str(), nullptr));
    }
    cacheFile.close();
    logger.log("Read the cache.", DEBUG);
}

void Cache::replace(std::vector<Card> &cards) {
    File cacheFile = LittleFS.open("cache.txt", "w");
    if (!cacheFile) {
        logger.log("Failed to open cache file. The cache cannot be read.", ERROR);
        cacheFile.close();
        return;
    }

    for (Card card : cards) {
        cacheFile.print((std::to_string(card)+"\n").c_str());
    }
    cacheFile.close();
    logger.log("Updated the cache.", DEBUG);
}