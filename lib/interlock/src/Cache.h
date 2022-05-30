#pragma once

#include "Logger.h"
#include <vector>
#include "Card.h"
#include <memory>

class Cache {
    private:
        Logger& logger;

    public:
        Cache() = delete;
        Cache(Logger& logger);
        void read(std::vector<Card>& cards);
        void replace(std::vector<Card> &cards);
};