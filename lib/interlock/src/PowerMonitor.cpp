#include "PowerMonitor.h"


void PowerMonitor::loop() {
    
}

PowerMonitor::PowerMonitor(Logger &logger, std::function<void()> powerOnCallback, std::function<void()> powerOffCallback) :
    logger{logger},
    powerOnCallback{powerOnCallback},
    powerOffCallback{powerOffCallback}
    {}
