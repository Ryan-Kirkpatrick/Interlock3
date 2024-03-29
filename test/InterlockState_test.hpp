#pragma once
#include <gtest/gtest.h>
#include "Indicator.hpp"
#include "mocks/MockStates.hpp"

TEST(InterlockState_test, STATE_UPDATES) {
    Logger logger;
    RFIDCardChecker cardChecker;
    Indicator indicator(IndicatorColors::WHITE);
    std::unique_ptr<AbstractState> currentState;
    currentState = std::make_unique<MockStateChangeState>(MockStateChangeState(cardChecker, logger));
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator.currentColor, IndicatorColors::GREEN);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator.currentColor, IndicatorColors::RED);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator.currentColor, IndicatorColors::RED);
}
