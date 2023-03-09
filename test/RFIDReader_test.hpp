#pragma once
#include <gtest/gtest.h>
#include "RFIDReader.hpp"
#include "mocks/MockSerial.hpp"

#ifdef RF125PS_READER

TEST(RFIDReader_test, Well_Formed_Card) {
    MockSerial serial;
    uint8_t bytes[] = {0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x38, 0xfb, 0x3};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    ASSERT_TRUE(card.has_value());
    EXPECT_EQ(card.value(), (unsigned long) 2006632);
}

TEST(RFIDReader_test, Well_Formed_Card_Missing_Stop_Byte) { // Desired behaviour for missing stop byte is a failed read.
    MockSerial serial;
    uint8_t bytes[] = {0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x38, 0xfb};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    EXPECT_FALSE(card.has_value());

}

TEST(RFIDReader_test, Well_Formed_Card_Between_Garbage) {
    MockSerial serial;
    uint8_t bytes[] = {0xba, 0x1b, 0x04, 0x95, 0x77, 0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x38, 0xfb, 0x3, 0x11, 0x41, 0x75, 0xc5, 0x38};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    ASSERT_TRUE(card.has_value());
    EXPECT_EQ(card.value(), (unsigned long) 2006632);

}

TEST(RFIDReader_test, Unterminated_Read) { // Missing stop byte
    MockSerial serial;
    uint8_t bytes[] = {0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    EXPECT_FALSE(card.has_value());

}

TEST(RFIDReader_test, Bad_Checksum) {
    MockSerial serial;
    uint8_t bytes[] = {0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x38, 0x01, 0x3};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    EXPECT_FALSE(card.has_value());

}


TEST(RFIDReader_test, Garbage) {
    MockSerial serial;
    uint8_t bytes[] = {0xba, 0x1b, 0x04, 0x95, 0x77, 0x2, 0x31, 0x33, 0x30, 0x30, 0x31, 0x45, 0x39, 0x45, 0x36, 0x32, 0xcc, 0x3, 0x11, 0x41, 0x75, 0xc5, 0x38};
    for (auto byte : bytes) {
        serial.addByte(byte);
    }

    auto card = RFIDReader::readCard(serial);
    EXPECT_FALSE(card.has_value());
}
#endif
