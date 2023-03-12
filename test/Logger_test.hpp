#pragma once
#include <gtest/gtest.h>
#include <random>
#include "Logger.hpp"
#include "Core.hpp"

std::string generateRandomString (unsigned int length) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<char> uni(48, 57);
    
    std::string result = "";
    for (unsigned int i = 0; i < length; i++) {
        result += uni(rng);
    }
    return result;
}

TEST(LoggerTest, Basic_No_Overwrite) {
    auto str = generateRandomString(Core::LOG_SIZE - 2U);

    Logger logger(false);
    logger.log(str);
    std::string testStr = logger.getLogs();
    EXPECT_EQ((str + "\n"), testStr);
}


TEST(LoggerTest, Basic_Too_Long) {
    auto str = generateRandomString(Core::LOG_SIZE + 20U);
    auto expectedStr = str.substr(0, Core::LOG_SIZE - 1);

    Logger logger(false);
    logger.log(str);
    std::string testStr = logger.getLogs();
    EXPECT_EQ((expectedStr), testStr);

}

TEST(LoggerTest, Overwrite) {
    auto strOverwritten = generateRandomString(Core::LOG_SIZE - 2U);
    auto strOverwrite = generateRandomString(Core::LOG_SIZE - 2U);

    Logger logger(false);
    logger.log(strOverwritten);
    logger.log(strOverwrite);
    std::string testStr = logger.getLogs();
    EXPECT_EQ((strOverwrite + "\n"), testStr);
}