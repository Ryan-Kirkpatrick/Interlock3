#include "RFIDReader.hpp"
#include <string>
#include <cstdlib>

namespace RFIDReader {



    #ifdef RF125PS_READER
    std::optional<RFIDCard> readCard(Stream &stream) {
        std::optional<RFIDCard> result;
        
        // Flush garbage until we find a start byte (0x02)
        while (stream.available()) {
            if (stream.read() == 0x02) {
                break;
            }
        }

        // Read card data, excluding stop byte
        char cardBytes[10] = {0};
        size_t numberOfBytes = stream.readBytes(cardBytes, 10);
        if (numberOfBytes != 10) {
            return result;
        }

        // Read checksum
        uint8_t checksum = 0;
        if (!stream.readBytes(&checksum, 1)) {
            return result;
        }

        // Check stop byte (0x03)
        uint8_t stopByte = 0;
        if ((!stream.readBytes(&stopByte, 1)) || (stopByte != 0x03)) {
            return result;
        }

        // Convert data to card number
        std::string cardStr(cardBytes, 10);

        // Calculate checksum and verify
        uint8_t calculatedChecksum = 0;
        uint8_t i = 0;
        do {
            calculatedChecksum ^= (uint8_t) strtoul(cardStr.substr(i, 2).c_str(), NULL, 16);
            i += 2;
        } while (i < 10);
        if (calculatedChecksum != checksum) {
            return result;
        }

        // Convert card data to 10 digit code
        result = strtoul(cardStr.substr(2).c_str(), NULL, 16);
        return result;

    }
    #endif
}
