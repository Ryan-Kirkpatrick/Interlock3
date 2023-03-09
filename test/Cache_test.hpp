#pragma once
#include <gtest/gtest.h>
#include "Cache.hpp"

#define SUITE_NAME Cache

CachedRFIDCards testCache1 = {
    .hashOfCards = "abc123",
    .cards = {10, 20, 30, 40, 50, 60, 70},
    .numberOfCards = 7
};

CachedRFIDCards testCache2 = {
    .hashOfCards = "xyz321",
    .cards = {11, 21, 31, 41, 51, 61},
    .numberOfCards = 6
};


TEST(SUITE_NAME, Update_Cache_Normal_Operation) {
    Cache cache;
    // Right now there is no cache, we should be unable to obtain results from the cache
    ASSERT_FALSE(cache.checkCard((RFIDCard) 10));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 20));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 2468));
    ASSERT_FALSE(cache.getHash().has_value());

    // Create the cache and test normal functions
    ASSERT_TRUE(cache.update(testCache1));
    ASSERT_TRUE(testCache1.hashOfCards == cache.getHash());
    ASSERT_TRUE(cache.checkCard((RFIDCard) 10));
    ASSERT_TRUE(cache.checkCard((RFIDCard) 30));
    ASSERT_TRUE(cache.checkCard((RFIDCard) 60));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 0));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 34));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 102));

    // Updating with same hash has no effect
    ASSERT_TRUE(cache.update(testCache1));
    ASSERT_TRUE(testCache1.hashOfCards == cache.getHash());
    ASSERT_TRUE(cache.checkCard((RFIDCard) 10));
    ASSERT_TRUE(cache.checkCard((RFIDCard) 30));
    ASSERT_TRUE(cache.checkCard((RFIDCard) 60));
    ASSERT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards

    // Update with a different set of cards (test it worked and that nothing from the last go is left over)
    ASSERT_TRUE(cache.update(testCache2));
    ASSERT_TRUE(testCache2.hashOfCards == cache.getHash());
    ASSERT_FALSE(cache.checkCard((RFIDCard) 10)); // Cards from last update
    ASSERT_FALSE(cache.checkCard((RFIDCard) 70)); // Cards from last update
    ASSERT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards
    ASSERT_TRUE(cache.checkCard((RFIDCard) 11)); // Cards from this update
    ASSERT_TRUE(cache.checkCard((RFIDCard) 31)); // Cards from this update
    ASSERT_TRUE(cache.checkCard((RFIDCard) 61)); // Cards from this update

    // Destruct the cache, and make a new one, ensuring it can read from flash correctly
    cache.~Cache();
    Cache cache2;
    
    // Check that everything is how it was
    ASSERT_TRUE(cache.update(testCache2));
    ASSERT_TRUE(testCache2.hashOfCards == cache.getHash());
    ASSERT_FALSE(cache.checkCard((RFIDCard) 10)); // Cards from last update
    ASSERT_FALSE(cache.checkCard((RFIDCard) 70)); // Cards from last update
    ASSERT_FALSE(cache.checkCard((RFIDCard) 0)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 34)); // Garbage cards
    ASSERT_FALSE(cache.checkCard((RFIDCard) 102)); // Garbage cards
    ASSERT_TRUE(cache.checkCard((RFIDCard) 11)); // Cards from this update
    ASSERT_TRUE(cache.checkCard((RFIDCard) 31)); // Cards from this update
    ASSERT_TRUE(cache.checkCard((RFIDCard) 61)); // Cards from this update

}