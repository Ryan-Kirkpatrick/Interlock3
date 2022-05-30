#pragma once

#include "Config.h"
#include "Card.h"
#include "Logger.h"

class RFIDReader {
    private:
        unsigned long lastReadTime = 0;
        Logger &logger;

    public:
        void flush();
        bool cardIsAvailable();
        Card readCard();
        RFIDReader(Logger &logger);
};
