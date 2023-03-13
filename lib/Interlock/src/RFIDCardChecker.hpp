#pragma once

#include "Types.hpp"
#include "PortalConnection.hpp"

class RFIDCardChecker {
    public:

        /**
         * @brief Returns true if the card is authorized for this device.
         */
        bool checkCard(RFIDCard card);
};
