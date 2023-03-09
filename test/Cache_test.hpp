#pragma once
#include <gtest/gtest.h>
#include "Cache.hpp"
#include <LittleFS.h>



TEST(Cache_Test, Update_Cache_Normal_Operation) {

    // Delete the file
    ASSERT_TRUE(LittleFS.begin());
    LittleFS.remove(Cache::CACHE_FILE_NAME);
    ASSERT_FALSE(LittleFS.exists(Cache::CACHE_FILE_NAME));

    // Setup
    CachedRFIDCards testCache1 = {
        .hashOfCards = "abc123",
        .cards = {0},
        .numberOfCards = 7
    };

    CachedRFIDCards testCache2 = {
        .hashOfCards = "xyz321",
        .cards = {0},
        .numberOfCards = 6
    };

    RFIDCard acc = 10;
    for (int i = 0; i < 8; i++) {
        testCache1.cards[i] = acc;
        acc += 10;
    }acc = 11;
    for (int i = 0; i < 7; i++) {
        testCache2.cards[i] = acc;
        acc += 10;
    }

    Cache cache;
    // Right now there is no cache, we should be unable to obtain results from the cache
    EXPECT_FALSE(cache.checkCard((RFIDCard) 0));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 10));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 20));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 2468));
    EXPECT_FALSE(cache.getHash().has_value());

    // Create the cache and test normal functions
    EXPECT_TRUE(cache.update(testCache1));
    EXPECT_EQ(testCache1.hashOfCards, cache.getHash().value());
    EXPECT_TRUE(cache.checkCard((RFIDCard) 10));
    EXPECT_TRUE(cache.checkCard((RFIDCard) 30));
    EXPECT_TRUE(cache.checkCard((RFIDCard) 60));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 0));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 34));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 102));

    // Updating with same hash has no effect
    EXPECT_TRUE(cache.update(testCache1));
    EXPECT_TRUE(testCache1.hashOfCards == cache.getHash());
    EXPECT_TRUE(cache.checkCard((RFIDCard) 10));
    EXPECT_TRUE(cache.checkCard((RFIDCard) 30));
    EXPECT_TRUE(cache.checkCard((RFIDCard) 60));
    EXPECT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards

    // Update with a different set of cards (test it worked and that nothing from the last go is left over)
    EXPECT_TRUE(cache.update(testCache2));
    EXPECT_TRUE(testCache2.hashOfCards == cache.getHash());
    EXPECT_FALSE(cache.checkCard((RFIDCard) 10)); // Cards from last update
    EXPECT_FALSE(cache.checkCard((RFIDCard) 70)); // Cards from last update
    EXPECT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards
    EXPECT_TRUE(cache.checkCard((RFIDCard) 11)); // Cards from this update
    EXPECT_TRUE(cache.checkCard((RFIDCard) 31)); // Cards from this update
    EXPECT_TRUE(cache.checkCard((RFIDCard) 61)); // Cards from this update

    // Destruct the cache, and make a new one, ensuring it can read from flash correctly
    cache.~Cache();
    Cache cache2;
    EXPECT_FALSE(cache2.getHash().has_value());
    
    // Check that everything is how it was
    EXPECT_TRUE(cache.update(testCache2));
    EXPECT_TRUE(testCache2.hashOfCards == cache.getHash());
    EXPECT_FALSE(cache.checkCard((RFIDCard) 10)); // Cards from last update
    EXPECT_FALSE(cache.checkCard((RFIDCard) 70)); // Cards from last update
    EXPECT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    EXPECT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards
    EXPECT_TRUE(cache.checkCard((RFIDCard) 11)); // Cards from this update
    EXPECT_TRUE(cache.checkCard((RFIDCard) 31)); // Cards from this update
    EXPECT_TRUE(cache.checkCard((RFIDCard) 61)); // Cards from this update

}