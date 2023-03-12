#include "Logger.hpp"
#include <Arduino.h>


Logger::Logger(bool useSerial) : useSerial{useSerial} {};

void Logger::log(std::string logText) {
    logText.append("\n");
    if (useSerial && Serial) {
        Serial.print(logText.c_str());
    }
    buffer.insert(logText.c_str());
}

const char* Logger::getLogs() {
    return buffer.getContents();
}

template<size_t size>
Logger::CircularBuffer<size>::CircularBuffer() : startOfBuffer{CyclicIndex<size>(0)}, endOfBuffer{CyclicIndex<size>(0)} {}

template<size_t size>
void Logger::CircularBuffer<size>::insert(const char *str) {
    // Find the size of the string and determine if it should be trimmed.
    size_t length = std::strlen(str);
    if (length > (size - 1)) {
        length = size -1;
    }

    // Place the (trimmed) string into the buffer
    for (size_t i = 0; i < length; i++) {
        buffer[endOfBuffer.value()] = str[i];
        endOfBuffer++;

        // If the buffer is full overwrite the start.
        if (endOfBuffer.value() == startOfBuffer.value()) {
            startOfBuffer++;
        }
    }

    // Remember null terminator
    buffer[endOfBuffer.value()] = '\0';
}

template<size_t size>
const char* Logger::CircularBuffer<size>::getContents() {
    shiftToStart();
    return buffer;
}

template<size_t size>
void Logger::CircularBuffer<size>::shiftToStart() {
    // Shift the buffer to the start
    while (startOfBuffer.value() != 0) {
        char swapTemp = buffer[0]; // Stores the first value to be placed back on the end later
        for (size_t i = 1; i < size; i++) {
            buffer[i-1] = buffer[i];
        }
        buffer[size-1] = swapTemp;

        // Update start and end
        startOfBuffer--;
        endOfBuffer--;
    }
}