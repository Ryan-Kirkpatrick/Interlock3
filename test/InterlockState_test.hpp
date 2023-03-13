#pragma once
#include <gtest/gtest.h>
#include "Indicator.hpp"
#include "mocks/MockStates.hpp"

TEST(InterlockState_test, STATE_UPDATES) {
    Logger logger;
    Indicator indicator(IndicatorColors::WHITE);
    std::unique_ptr<AbstractState> currentState;
    currentState = std::make_unique<MockStateChangeState>(MockStateChangeState(logger));
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::GREEN);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::RED);
    currentState = currentState->run(indicator);
    ASSERT_EQ(indicator._currentColor, IndicatorColors::RED);
}
