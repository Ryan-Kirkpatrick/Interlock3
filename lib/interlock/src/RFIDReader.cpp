#include "RFIDReader.h"
#include <Arduino.h>
#include "Config.h"

bool RFIDReader::cardIsAvailable() {
    // Ignore reads that are too close together in time
    if ((millis() - this->lastReadTime) / 1000 < Config::rfidIgnoreTime) return false;
    return Serial.available();
}

// Clear the serial buffer
void RFIDReader::flush() {
    int count;
    for (count = 1; Serial.available(); count++) {
        Serial.read();
    }
    logger.log(std::string("Flushed bytes from serial buffer: ").append(std::to_string(count)), DEBUG);
}

// Returns the RFID card number of what was read.
// No checking is done for the validity of the card or the data. It will return whatever it read from the serial buffer.
// Returns negative values for logical errors and for reads that are too close together.
long RFIDReader::readCard() {
    if (!cardIsAvailable()) {return -1;}
    delay(250); // Ensure there was enough time for a full card to be read 
    
    #ifdef RF125PS_READER
    char tagData[8];                // Stores raw tag bytes
    unsigned char byteCounter = 0;  // Count how many bytes have been read from serial
    unsigned char tagDataIndex = 0;
    while (Serial.available()) {
        // Skip unused bytes and flush and extra bytes
        if (byteCounter < 3 || byteCounter > 10) {
            byteCounter++;
            Serial.read();
            continue;
        }

        // Load useful bytes into tagData
        tagData[tagDataIndex] = Serial.read();

        // Increment
        tagDataIndex++;
        byteCounter++;
    }

    // Convert raw bytes to hex number represented in ASCII string
    String tagStr = String(tagData);

    // Convert hex number to decimal
    flush();
    return strtol(tagStr.c_str(), nullptr, 16);
    #endif
    #ifdef OLD_READER
    char tagBytes[6];

    if (Serial.readBytes(tagBytes, 5) == 5) {
        uint32_t cardId = 0;
        //tagBytes[6] = 0;

        for (int i = 0; i < 4; i++) {
            cardId = cardId << 8 | tagBytes[i];
        }
        flushSerial();
        return cardId;
    }
    flushSerial();
    return -1;
    #endif
}

RFIDReader::RFIDReader(Logger &logger) : logger{logger} {}