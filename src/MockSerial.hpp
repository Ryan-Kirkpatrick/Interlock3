#pragma once

#include <Arduino.h>
#include <queue>


class MockSerial : public Stream {
    public:
        int available() override {
            return bytes.size();
        }

        int peek() override {
            if (!available()) {
                return -1;
            }
            return bytes.front();
        }

        int read() override {
            if (!available()) {
                return -1;
            }
            auto result = peek();
            bytes.pop();
            return result;
        }

        // Should not be called.
        size_t write(uint8_t _) override {
            Serial.println("\n :( Sad times\n");
            return 0;
        }
        
        void addByte(uint8_t byte) {
            bytes.push(byte);
        }


    private:
        std::queue<uint8_t> bytes;


};