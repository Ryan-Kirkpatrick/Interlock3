#pragma once

#include "Types.hpp"
#include "PortalConnection.hpp"
#include "Cache.hpp"

class RFIDCardChecker {
    public:
        RFIDCardChecker(IPortalConnection &portal, Cache &cache);

        /**
         * @brief Returns true if the card is authorized for this device.
         */
        bool checkCard(RFIDCard card);

    protected:
        IPortalConnection &portal;
        Cache cache;


        
};
