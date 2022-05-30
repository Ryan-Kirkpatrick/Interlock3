#pragma once

#include <functional>
#include "Logger.h"

class PowerMonitor {
    private:
        Logger &logger;
        std::function<void()> powerOnCallback;
        std::function<void()> powerOffCallback;
    public:
        void loop();
        PowerMonitor(Logger &logger, std::function<void()> powerOnCallback, std::function<void()> powerOffCallback);
};