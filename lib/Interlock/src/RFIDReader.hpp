#pragma once
#include "Types.hpp"

#include <optional>

#include <Arduino.h>

namespace RFIDReader {
    /**
     * @brief Reads and RFID card from a stream.
     * 
     * @param serial The stream to read from, likely Serial. Will be altered.
     * @return std::optional<RFIDCard> Will have the value of the RFID card if there was a successful read.
     * Otherwise the optional will have no value. 
     */
    std::optional<RFIDCard> readCard(Stream &stream);
}